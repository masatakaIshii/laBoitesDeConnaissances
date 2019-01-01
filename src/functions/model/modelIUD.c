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
        printf("Warning[MYSQL] : none row affected\n");
    }

    return affectedRow;
}
