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
void setPreparedQuery(App *app, char *query, char **tablesNames, int numberTables, char **paramsNames, char **paramsValues){

    MySqlStmtManager *stmtManager = &app->model.query.stmtManager;
    stmtInitialisation(app, stmtManager);

    if (mysql_stmt_prepare(stmtManager->stmt, query, strlen(query))){

        printf("Error [MYSQL_STMT] in preparation of stmt : %s\n" , mysql_stmt_error(stmtManager->stmt));
        quitApp(app);
        exit(EXIT_FAILURE);
    }

    //load numberParams, numberTables, tables and params names in stmtManager
    stmtManager->numberParams = mysql_stmt_param_count(stmtManager->stmt);
    stmtManager->numberTables = numberTables;
    //loadStmtManager(app, stmtManager, tablesNames, paramsNames);

    getParamsNames(app, stmtManager, query, stmtManager->numberParams);
    //load app->model.tables
    //readAndGetNumberAndNamesAndStructTables(app, &app->model);

    /*
    TODO : remplir dans stmtManager la partie MySqlParamsBind par rapport aux types des params :
    - malloc la structure param en fonction de son nombre
    - déterminer le type de param par rapport à son nom, grâce à MysqlTablesStruct
    - après avoir trouver le type, remplir en fonction sa structure param
    */
}

void loadStmtManager(App *app,MySqlStmtManager * stmtManager, char **tablesNames, char **paramsNames) {

    int i;

    stmtManager->paramsNames = malloc(sizeof(Varchar) * stmtManager->numberParams);
    for(i = 0; i < stmtManager->numberParams; i++) {
        strcpy(stmtManager->paramsNames[i], paramsNames[i]);
    }

    stmtManager->tablesNames = malloc(sizeof(Varchar) * stmtManager->numberTables);
    for (i = 0; i < stmtManager->numberTables; i++){
        strcpy(stmtManager->tablesNames[i], tablesNames[i]);
    }
}


void getParamsNames(App *app, MySqlStmtManager  *stmtManager, char *query, int numberParams) {
    char temp1[1000];
    char temp2[1000];
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

        printf("\ntemp2 : %s\n", temp2);
        getBeginAndEndOfParamName(temp2, &min, &max);

        mySubstring(name, temp2, min, max);
        printf("name : %s\n", name);
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
        printf("char ascii: %d\n", query[strlen(query) - 1]);
        printf("char :%c\n" , query[strlen(query) - 1]);
        printf("number char of empty : %d\n", ' ');
        printf("number char of = : %d\n", '=');

        //trouver la derniere lettre du parametre
        if (query[strlen(query) - 1] != '=' && query[strlen(query) - 1] != ' ') {
            *max = strlen(query);
            printf("char in *max : %c\n", query[*max]);
            printf("*max : %d\n", *max);
        }

        // trouver la premiere lettre du parametre apres avoir trouver la derniere
        if (*max != -1){
            if (strrchr(query, ' ')){
                *min = strrchr(query, ' ') - query + 1;
                printf("char in *min : %c\n", query[*min]);
                printf("*min : %d\n", *min);
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

int getTypeField(char *paramName, MySqlTable *tables, Varchar *tablesNames, int numberTables) {
    char *table;
    int typeField = -1;
    int i;
    int j;

    if (numberTables > 1) {
        getProperFieldAndTable(&paramName, &table);
    } else {
        table = tablesNames[0];
    }

    for (i = 0; i < numberTables; i++) {
        for (j = 0; j < tables[i].numberField; j++) {
            if (table == tables[i].tableName) {
                if (strncmp(paramName, tables[i].listFieldsNames[j], strlen(paramName) + 1) == 0) {
                    printf("le type %s de paramName est de :%d\n", paramName, tables[i].listFieldsTypes[j]);
                    typeField = tables[i].listFieldsTypes[j];
                }
            }
        }
        printf("\n");
    }

    return typeField;
}
