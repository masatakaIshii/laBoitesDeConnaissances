/*
** Filename : mysqlIUD.c
**
** Made by  : Masataka ISHII
**
** Description  : insert, update and delete functions used API C MySQL for select data in database
*/
#include "../../headers/model/modelIUD.h"

int queryIUD(App *app, const char *currentQuery) {
    int affectedRows = 0;
    int result;

    result = mysql_query(&app->mysql, currentQuery);
    verifyMYSQLIntResult(app, result);

    affectedRows = mysql_affected_rows(&app->mysql);

    return affectedRows;
}

int preparedQueryIUD(App *app, const char *currentQuery, char **tableNames, int numberTables, char **paramsName, char **paramsValues,  int numberParams) {
    int affectedRow = 0;
    int i;
    MySqlStmtManager stmtManager;

    loadStmtManager(app, &stmtManager, numberTables, numberParams, currentQuery);

    loadTablesStruct(app, &stmtManager, tableNames);

    loadBindParams(app, &stmtManager, paramsName, paramsValues);

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
    quitStmtManager(&stmtManager);

    return affectedRow;
}


