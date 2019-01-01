/*
** Filename : mysqlIUD.c
**
** Made by  : Masataka ISHII
**
** Description  : insert, update and delete functions used API C MySQL for select data in database
*/
#include "../../headers/model/modelIUD.h"
#include "../../headers/model/modelInit.h"

/**
*@brief to send simple INSERT, UPDATE or DELETE query
*
*@param (App *) app - structure of application that content all structures
*@param (const char *) currentQuery - string of query
*/
int queryIUD(App *app, const char *currentQuery) {
    int affectedRows = 0;
    int result;

    result = mysql_query(app->model.mysql, currentQuery);
    verifyMYSQLIntResult(app, result);

    affectedRows = mysql_affected_rows(app->model.mysql);

    return affectedRows;
}


int sendPreparedQueryIUD(App *app, const char *currentQuery) {
    int affectedRow = 0;
    int i;

    MySqlStmtManager *stmtManager = &app->model.query.stmtManager;

    printf("numberParams :%d\n", stmtManager->numberParams);
    for (i = 0; i < stmtManager->numberParams; i++) {
        printf("stmtManager->buffersBind[%d].buffer : %s\n", i, stmtManager->buffersBind[i].buffer);
        printf("stmtManager->buffersBind[%d].buffer_length : %u\n", i, stmtManager->buffersBind[i].buffer_length);
        printf("stmtManager->buffersBind[%d].length : %p\n", i, stmtManager->buffersBind[i].length);
        printf("stmtManager->buffersBind[%d].buffer : %p\n", i, stmtManager->buffersBind[i].buffer);
    }
    if (strncmp(stmtManager->currentQuery, currentQuery, strlen(currentQuery) + 1) != 0) {
        printf("Error[MYSQL] : problem in sendPreparedQueryIUD, currentQuery is not attempt\n");
        printf("currentQuery : %s\n", currentQuery);
        printf("attempt query : %s\n", stmtManager->currentQuery);
        quitApp(app);
        exit(EXIT_FAILURE);
    }

    if (mysql_stmt_execute(stmtManager->stmt)) {
        printf("Error[MYSQL] : %s\n", mysql_stmt_error(stmtManager->stmt));
        quitApp(app);
        exit(EXIT_FAILURE);
    }

    affectedRow = mysql_stmt_affected_rows(stmtManager->stmt);
    if (affectedRow <= 0){
        printf("Error[MYSQL] : less than 1 row is affected\n");
        quitApp(app);
        exit(EXIT_FAILURE);
    }

    //loadStmtManager(app, stmt, numberTables, numberParams, currentQuery);
//
//    printf("stmt.numberParams : %d\n", stmt.numberParams);
//    printf("stmt.numberParams : %d\n", stmt.);
    //readAndGetNumberAndNamesAndStructTables(app, &app->model);



    //loadBindParams(app, &stmtManager, paramsName, paramsValues);

    //printf("numberfield : %d\n", stmtManager.tables.numberField);
    //loadParams(app, &stmtManager, );

    /*
    TODO :
        il faut check si loadTablesStruct fonctionne
        faire fonctioins :
            loadParamBind(app, &stmtManager, paramsNames);
            loadBufferBind(app, &stmtManager);
        puis executer;
    */
    //int *arrayTypeParams = getArrayTypeParams(app, &stmtManager, paramsName);
    //int arrayLengthsParams = getArrayLengthParams(app, tables, numberTables, paramsName, numberParams, arrayTypeParams);


    //MYSQL_BIND *params = bindParams(app, tables, numberTables, paramsName, paramsValues, numberParams);


    /*
    verify if '?' in currentQuery correspond to numberValues
    specialParamValues = escape special char for paramValues
    getTable by currentQuery;



    */
    //quitStmtManager(&stmtManager);

    return affectedRow;
}
