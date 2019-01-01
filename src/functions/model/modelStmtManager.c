/*
** Filename : modelStmtManager.c
**
** Made by  : Masataka ISHII
**
** Description  : set stmtManager's structure functions that uses API C MySQL
*/

#include "../../headers/model/modelStmtManager.h"
/**
*@brief setPreparedQuery : for fill the structure stmtManager with the exception of *bufferBind
*
*@param (char **) tablesNames : list of tables names
*@param (int) numberTables : number of tables used for the prepared query
*@param (char **) paramsNames : list of parameters names used for the prepared query
*@param (int) numberTables : number of params that use for the prepared query
*@param (char **) paramsValues : list of parameters values used for the prepared query
*/
void setPreparedQuery(App *app, char *query, char **tablesNames, int numberTables){

    MySqlStmtManager *stmtManager = &app->model.query.stmtManager;

    stmtInitialisation(app, stmtManager);
    if (mysql_stmt_prepare(stmtManager->stmt, query, strlen(query))){

        printf("Error [MYSQL_STMT] in preparation of stmt : %s\n" , mysql_stmt_error(stmtManager->stmt));
        quitApp(app);
        exit(EXIT_FAILURE);
    }

    stmtManager->currentQuery = malloc(sizeof(char) * (strlen(query) + 1));
    strcpy(stmtManager->currentQuery, query);

    //load numberParams, numberTables, tables and params names in stmtManager
    loadStmtManager(app, stmtManager, tablesNames, numberTables);

    getParamsNames(app, stmtManager, query, stmtManager->numberParams);

    //load app->model.tables
    readAndGetNumberAndNamesAndStructTables(app, &app->model);

    loadStmtManagerBindTypes(app, &app->model);

    freeStructTableMysql(&app->model);
}

void loadStmtManager(App *app,MySqlStmtManager * stmtManager, char **tablesNames, int numberTables) {
    int i;

    stmtManager->numberParams = mysql_stmt_param_count(stmtManager->stmt);
    stmtManager->numberTables = numberTables;

    stmtManager->tablesNames = malloc(sizeof(Varchar) * stmtManager->numberTables);

    for (i = 0; i < stmtManager->numberTables; i++){
        strcpy(stmtManager->tablesNames[i], tablesNames[i]);
    }
}


void getParamsNames(App *app, MySqlStmtManager  *stmtManager, char *query, int numberParams) {
    char temp1[MAX_TEXT];
    char temp2[MAX_TEXT];
    int max = -1, min = -1;
    Varchar name;
    int currentLenght = 0;
    int i;

    strcpy(temp1, query);
    for (i = 0; i < numberParams; i++) {
        //Chercher la premiere occurence contenant comme char '?'
        strncpy(temp2, temp1, strchr(temp1, '?') - temp1);

        //obtenir du debut a la premiere occurence '?' pour trouver son parametre
        temp2[strchr(temp1, '?') - temp1] = '\0';

        getBeginAndEndOfParamName(temp2, &min, &max);

        mySubstring(name, temp2, min, max);

        addStringInList(app, name, &stmtManager->paramsNames, &currentLenght);

        //Enlever la premiere occurence '?' et initialisez max et min
        temp1[strchr(temp1, '?') - temp1] = '_';
        max = -1;
        min = -1;
    }
}

void getBeginAndEndOfParamName(char *query, int *min, int *max) {
    int length = strlen(query);

    while (length >= 0 && (*max < 0 || *min < 0)) {

        //trouver la derniere lettre du parametre
        if (query[strlen(query) - 1] != '=' && query[strlen(query) - 1] != ' ') {
            *max = strlen(query);
        }

        // trouver la premiere lettre du parametre apres avoir trouver la derniere
        if (*max != -1){
            if (strrchr(query, ' ')){
                *min = strrchr(query, ' ') - query + 1;
                break;
            } else {
                printf("Warning : Problem of query instruction.\n");
            }
        }
        //s'il n'y a pas de *max et de *min, reduire la chaine en enlevant le dernier charactere
        query[strlen(query) - 1] = '\0';
        length = strlen(query);

        if (length == 0){
            printf("Warning : This query is not prepared\n");
            break;
        }
    }
}


void mySubstring(Varchar newString, const char* stringToSub, int minIndex, int maxIndex) {
    int length = maxIndex - minIndex + 1;

    strncpy(newString, stringToSub + minIndex, length);
    *(newString + length) = '\0';
}

void addStringInList(App *app, Varchar paramName, Varchar **listString, int *currentLength) {
    Varchar *inter;
    int length = *currentLength;
    int i;

    //printf("\n in addStringInlist\n");
    if ((*listString) == NULL) {
        inter = malloc(sizeof(Varchar));
        verifyPointer(app, inter, "Problem malloc inter in addStringInList\n");
    } else {
        inter = malloc(sizeof(Varchar) * (length + 1));
        verifyPointer(app, inter, "Problem malloc inter in addStringInList\n");
        for (i = 0; i < length; i++) {
            strcpy(inter[i], (*listString)[i]);
        }
    }

    strcpy(inter[length], paramName);
    (*currentLength)++;

    if ((*listString) != NULL){
        free(*listString);
    }
    (*listString) = inter;
}

/*
TODO : adapter cette fonction pour la requête préparée
*/
void loadStmtManagerBindTypes(App *app, Model *model) {

    int i;
    MySqlStmtManager *stmtManager = &model->query.stmtManager;

    stmtManager->buffersBind = malloc(sizeof(MYSQL_BIND) * stmtManager->numberParams);
    memset(stmtManager->buffersBind, 0, sizeof(MYSQL_BIND));
    verifyPointer(app, stmtManager->buffersBind, "Problem malloc stmtManager->params in loadStmtManagerParams");
    for (i = 0; i < stmtManager->numberParams; i++) {

        stmtManager->buffersBind[i].buffer_type = getTypeField(stmtManager->paramsNames[i], model, stmtManager);


    }
}

int getTypeField(Varchar paramName, Model *model, MySqlStmtManager *stmtManager) {
    MySqlTable *tables = model->tables;
    Varchar table;
    int typeField = -1;
    Varchar *tablesNames = stmtManager->tablesNames;
    int numberTables = model->numberAllTables;
    int i;
    int j;

    if (stmtManager->numberTables > 1) {
        getProperFieldAndTable(paramName, table);

    } else {
        strcpy(table, tablesNames[0]);
    }

    for (i = 0; i < numberTables; i++) {
        if (strncmp(table, tables[i].tableName, strlen(table) + 1) == 0) {
            for (j = 0; j < tables[i].numberField; j++) {
                if (strncmp(paramName, tables[i].listFieldsNames[j], strlen(paramName) + 1) == 0) {
                    typeField = tables[i].listFieldsTypes[j];
                }
            }
        }
    }

    return typeField;
}

/**
*@brief if field is juncture, separated "table.field" to "table" and "field"
*
*@param field : address of field
*@param table : address of table
*/
void getProperFieldAndTable(Varchar field, Varchar table) {
    char temp[255];

    //Check if field is juncture
    if (strchr(field, '.')) {
        strcpy(temp, field);
        sprintf(field, "%s", strchr(temp, '.') + 1);

        //verify if table content a value, if table is NULL it'll be affected
        strcpy(table, temp);
        table[strchr(temp, '.') - temp] = '\0';

    }
}
//
//void fillParams(App *app, int paramType, MySqlParamsBind *params, char *paramValue) {
//    if (paramType == MYSQL_TYPE_STRING || paramType == MYSQL_TYPE_VAR_STRING || paramType == MYSQL_TYPE_BLOB) {
//        fillParamString(app, params, paramValue);
//    }
//    if (paramType == MYSQL_TYPE_LONG || paramType == MYSQL_TYPE_INT24) {
//        fillParamInt(app, params, paramValue);
//    }
//    if (paramType == MYSQL_TYPE_DOUBLE) {
//        fillParamDouble(app, params, paramValue);
//    }
//    if (paramType == MYSQL_TYPE_DATETIME) {
//        fillParamDatetime(app, params, paramValue);
//    }
//    params->paramsIsNull = (strlen(paramValue) == 0) ? 1 : 0;
//}
//
//void fillParamsString(App *app, MySqlParamsBind *params, char *paramValue) {
//    strcpy(params->paramsString, paramValue);
//    params->paramsStrLen = strlen(paramValue);
//}
//
//void fillParamInt(App *app, MySqlParamsBind *params, char *paramValue) {
//
//    if (strlen(paramValue) == 0) {
//        params->paramNumber = 0;
//    } else if (atoi(paramValue) == 0 && paramsValue[0] != '0') {
//        printf("Problem with %s paramValue in fillParamInt\n", paramValue);
//        quitApp(app);
//    } else {
//        params->paramNumber = atoi(paramsValue);
//    }
//    params->paramsLengths = 0;
//    params->paramsStrLen = 0;
//}
//
//void fillParamDouble(App *app, MySqlParamsBind *params, char *paramValue) {
//
//    if (atof(paramValue) == 0 && paramsValue[0] != '0') {
//        printf("Problem with %s paramValue in fillParamDouble\n", paramValue);
//    } else {
//        params->paramDouble = atof(paramValue);
//    }
//    params->paramsLengths = 0;
//}
//
//void fillParamDatetime(App *app, MySqlParamsBind *params, char *paramValue) {
//
//    unsigned year, month, day, hour, minute, second;
//
//    sscanf(paramValue, "%u-%u-%u %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
//
//    printf("paramsDateTime.year : %u\n", params->paramsDateTime.year);
//    printf("paramsDateTime.month : %u\n", params->paramsDateTime.month);
//    printf("paramsDateTime.day : %u\n", params->paramsDateTime.day);
//    printf("paramsDateTime.hour : %u\n", params->paramsDateTime.hour);
//    printf("paramsDateTime.minute : %u\n", params->paramsDateTime.minute);
//    printf("paramsDateTime.second : %u\n", params->paramsDateTime.second);
//}
