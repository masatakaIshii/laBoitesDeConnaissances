/*
** Filename : createModel.c
**
** Made by  : Masataka ISHII
**
** Description  : getting data for selected table
*/

#include "../../headers/model/createModel.h"

SelectQuery getSelectedTable(App *app, char *tableName, char *idParent){
    char query[MAX_VARCHAR];

    if (idParent == NULL){
        sprintf(query, "SELECT * FROM %s", tableName);
    } else if (strcmp(tableName, "list") == 0){
        sprintf(query, "SELECT * FROM %s WHERE id_box = %s", tableName, idParent);
    } else if (strcmp(tableName, "card") == 0){
        sprintf(query, "SELECT * FROM %s WHERE id_list = %s", tableName, idParent);
    }

    return getSelectQuery(app, query);
}
