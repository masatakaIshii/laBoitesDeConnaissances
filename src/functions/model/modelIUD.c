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

int preparedQueryIUD(App *app, const char *currentQuery, const char **paramValues, unsigned int *numberValues) {


    /*
    verify if '?' in currentQuery correspond to numberValues
    specialParamValues = escape special char for paramValues
    getTable by currentQuery;


    */
}
