/*
** Filename : modelStmtManager.c
**
** Made by  : Masataka ISHII
**
** Description  : set stmtManager's structure functions that uses API C MySQL
*/

#include "../../../headers/model/modelHelper/modelStmtManager.h"
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

    if (stmtManager != NULL) {
        quitStmtManager(stmtManager);
    }
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
