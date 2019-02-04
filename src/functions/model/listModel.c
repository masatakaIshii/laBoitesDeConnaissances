/*
** Filename : listModel.c
**
** Made by  : Baptiste LEGO
**
** Description  : data model for list table
*/

#include <stdlib.h>
#include <stdio.h>
#include "../../headers/model/modelHelper/modelSelect.h"

SelectQuery getAllLists(App *app){
    return getSelectQuery(app, "SELECT * FROM list");
}

SelectQuery getListsFromBox(App *app, char *boxId){
    char query[50];
    strcpy(query, "SELECT * from list WHERE id_box=");
    strcat(query, boxId);

    return getSelectQuery(app, query);
}
