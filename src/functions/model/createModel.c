/*
** Filename : createModel.c
**
** Made by  : Masataka ISHII
**
** Description  : getting data for selected table
*/

#include "../../headers/model/createModel.h"

SelectQuery getSelectedTable(App *app, char *tableName){
    char query[MAX_VARCHAR];
    sprintf(query, "SELECT * FROM %s", tableName);

    return getSelectQuery(app, query);
}
