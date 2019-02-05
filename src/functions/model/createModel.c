/*
** Filename : createModel.c
**
** Made by  : Masataka ISHII
**
** Description  : getting data for selected table
*/

#include "../../headers/model/createModel.h"

SelectQuery getSelectedTable(App *app, char *tableName, char **info){
    char query[MAX_VARCHAR];

    if (info == NULL){
        sprintf(query, "SELECT * FROM %s", tableName);
    } else if (strcmp(tableName, "list") == 0){
        sprintf(query, "SELECT * FROM %s WHERE id_box = %s", tableName, info[0]);
    } else if (strcmp(tableName, "card") == 0){
        sprintf(query, "SELECT * FROM %s WHERE id_list = %s", tableName, info[0]);
    }

    return getSelectQuery(app, query);
}
