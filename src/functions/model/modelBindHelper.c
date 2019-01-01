/*
** Filename : modelBindHelper.c
**
** Made by  : Masataka ISHII
**
** Description  : functions used API C MySQL for bind prepared queries
*/

#include "../../headers/model/modelBindHelper.h"
void setBindParams(App *app, char **paramsValues) {

    MySqlStmtManager *stmtManager = &app->model.query.stmtManager;

    loadBindParams(app, stmtManager, paramsValues);

    if (mysql_stmt_bind_param(stmtManager->stmt, stmtManager->buffersBind)) {
        printf("Error[MYSQL_STMT_BIND] : %s\n", mysql_stmt_error(stmtManager->stmt));
        quitApp(app);
        exit(EXIT_FAILURE);
    }
}

void loadBindParams(App *app, MySqlStmtManager *stmtManager, char **paramsValues){
    int i;
    enum_field_types typeParam;

    stmtManager->params = malloc(sizeof(MySqlParamsBind) * stmtManager->numberParams);
    for (i = 0; i < stmtManager->numberParams; i++) {

        typeParam = stmtManager->buffersBind[i].buffer_type;
        if (typeParam == MYSQL_TYPE_BLOB || typeParam == MYSQL_TYPE_STRING || typeParam == MYSQL_TYPE_VAR_STRING){
            bindParamString(app, i, stmtManager, paramsValues[i]);
        }

        if (typeParam == MYSQL_TYPE_LONG || typeParam == MYSQL_TYPE_SHORT || typeParam == MYSQL_TYPE_TINY) {
            bindParamInt(app, i, stmtManager, paramsValues[i]);
        }

        if (typeParam == MYSQL_TYPE_DATE || typeParam == MYSQL_TYPE_DATETIME || typeParam == MYSQL_TYPE_TIMESTAMP) {
            bindParamDate(app, i, stmtManager, paramsValues[i]);
        }

        if (typeParam == MYSQL_TYPE_DOUBLE) {
            bindParamDouble(app, i, stmtManager, paramsValues[i]);
        }
    }
}

void bindParamString(App *app, int index, MySqlStmtManager *stmtManager, char *paramValue) {
    stmtManager->params[index].paramsLengths = strlen(paramValue);
    stmtManager->params[index].paramsIsNull = (strncmp(paramValue, "", strlen(paramValue)) == 0) ? 1 : 0;

    stmtManager->params[index].paramsString = malloc(sizeof(char) * (strlen(paramValue) + 1));
    strcpy(stmtManager->params[index].paramsString, paramValue);

    stmtManager->buffersBind[index].buffer_length = stmtManager->params[index].paramsLengths + 1;
    stmtManager->buffersBind[index].buffer = (char *)stmtManager->params[index].paramsString;
    if (stmtManager->params[index].paramsIsNull == 1) {
        stmtManager->buffersBind[index].is_null = (my_bool*)&stmtManager->params[index].paramsIsNull;
    } else {
        stmtManager->buffersBind[index].is_null = 0;
    }
    stmtManager->buffersBind[index].length = &stmtManager->params[index].paramsLengths;

    printf("buffer : %s\n", stmtManager->buffersBind[index].buffer);
}

void bindParamInt(App *app, int index, MySqlStmtManager *stmtManager, char *paramValue) {
    stmtManager->params[index].paramsIsNull = (strncmp(paramValue, "", strlen(paramValue)) == 0) ? 1 : 0;
    stmtManager->params[index].paramNumber = atoi(paramValue);

    if (stmtManager->params[index].paramsIsNull == 1) {
        if (atoi(paramValue) == 0 && paramValue[0] != '0') {
            printf("Problem with paramValue and its type\n");
            quitApp(app);
        }
    }

    stmtManager->buffersBind[index].buffer = (void *)&stmtManager->params[index].paramNumber;
    if (stmtManager->params[index].paramsIsNull == 1) {
        stmtManager->buffersBind[index].is_null = (my_bool*)&stmtManager->params[index].paramsIsNull;
    } else {
        stmtManager->buffersBind[index].is_null = 0;
    }
    stmtManager->buffersBind[index].length = 0;
}

void bindParamDate(App *app, int index, MySqlStmtManager *stmtManager, char *paramValue) {
    MYSQL_TIME *time = &stmtManager->params[index].paramsDateTime;
    stmtManager->params[index].paramsIsNull = (strncmp(paramValue, "", strlen(paramValue)) == 0) ? 1 : 0;

    if (stmtManager->params[index].paramsIsNull == 0){
        sscanf(paramValue, "%u-%u-%u %u:%u:%u", &time->year, &time->month, &time->day, &time->hour, &time->minute, &time->second);
    }
    stmtManager->buffersBind[index].buffer = (void *)time;
    if (stmtManager->params[index].paramsIsNull == 1) {
        stmtManager->buffersBind[index].is_null = (my_bool*)&stmtManager->params[index].paramsIsNull;
    } else {
        stmtManager->buffersBind[index].is_null = 0;
    }
    stmtManager->buffersBind[index].length = 0;
}

void bindParamDouble(App *app, int index, MySqlStmtManager *stmtManager, char *paramValue) {
    stmtManager->params[index].paramDouble = atof(paramValue);
    stmtManager->params[index].paramsIsNull = (strncmp(paramValue, "", strlen(paramValue)) == 0) ? 1 : 0;

    if (stmtManager->params[index].paramsIsNull == 0) {
        if (atof(paramValue) == 0 && paramValue[0] != '0') {
            printf("Problem with paramValue and its type\n");
            quitApp(app);
        }
    }
    stmtManager->buffersBind[index].buffer = (void *)&stmtManager->params[index].paramDouble;
    if (stmtManager->params[index].paramsIsNull == 1) {
        stmtManager->buffersBind[index].is_null = (my_bool*)&stmtManager->params[index].paramsIsNull;
    } else {
        stmtManager->buffersBind[index].is_null = 0;
    }

    stmtManager->buffersBind[index].length = 0;
}

//
//int *getArrayTypeParams(App *app, MySqlTable *tables, int numberTables, char **paramsName, int numberParams) {
//    int typeField;
//    int i;
//    int *arrayTypesParams = calloc(numberParams, sizeof(int*));
//    verifyPointer(app, arrayTypesParams, "Problem malloc arrayTypesParams");
//
//    for (i = 0; i < numberParams; i++) {
//        typeField = getTypeField(paramsName[i], tables, numberTables);
//        if (typeField == -1) {
//            verifyPointer(app, NULL, "Problem with typeField");
//        }
//        arrayTypesParams[i] = typeField;
//    }
//
//    return arrayTypesParams;
//}

//
//**
//*@brief bind parameters values and metadatas for the prepared query
//*
//*@param (App *) app  - structure of app to use mysql
//*@param (char **) tableNames - names of tables concern to the query
//*@param (char **) paramsName - names of fields concern to the params
//*@param (char **) paramsValues - values of params to bind
//*@param (int) numberParams - number of params
//*@return (MYSQL_BIND *) params - all params completed
//*/
//MYSQL_BIND *bindParams(App *app, MySqlTable *tables, int numberTables, char **paramsName, char **paramsValues,  int numberParams){
//
//    int i;
//
//    unsigned int typeParam;
//
//    MYSQL_BIND *params = malloc(sizeof(MYSQL_BIND) * numberParams);
//    memset(params, 0, numberParams);
//
//    for (i = 0; i < numberParams; i++) {
//        params[i] = bindOneParam(app, paramsName[i], paramsValues[i], tables, numberTables);
//    }
//
//    /*TODO :
//        -obtenir tableau de length des params, si c'est des num => 0;
//        -adapter bindParams pour mettre en paramètre MySqlTable
//    */
//
//    /*
//    for
//        get name
//        get buffer_type(name, table->arrayField, table->arrayTypeField, table->numberField);
//        get buffer(paramsValues[i], type);
//        get buffer_length(paramsValues[i], type);
//        is_null = 0;
//        get length = if(type) ? strlen(buffer) : 0
//
//    */
//
//    return params;
//}
//
//
//MYSQL_BIND bindOneParam(App *app, char *paramsName, char *paramsValues, MySqlTable *tables, int numberTables) {
//
//    MYSQL_BIND param;
//    char table[255];
//    char field[255];
//
//    strcpy(field, paramsName);
//    printf("%s\n", field);
//
//    //param.buffer_type = getTypeOfField();
//
//    /*
//    for
//    */
//
//    return param;
//}
