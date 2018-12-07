/*
** Filename : mysqlIUD.c
**
** Made by  : Masataka ISHII
**
** Description  : insert, update and delete functions used API C MySQL for select data in database
*/
#include "../../headers/model/modelIUD.h"

int queryIUD(MYSQL *mysql, const char *currentQuery) {
    int affectedRows = 0;

    mysql_query(mysql, currentQuery);
    affectedRows = mysql_affected_rows(mysql);

    return affectedRows;
}
