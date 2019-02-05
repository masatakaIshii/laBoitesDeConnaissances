/*
** Filename : boxModel.c
**
** Made by  : Baptiste LEGO
**
** Description  : data model for box table
*/

#include <stdlib.h>
#include <stdio.h>
#include "../../headers/model/modelHelper/modelSelect.h"

SelectQuery getBoxes(App *app){
    return getSelectQuery(app, "SELECT * from box");
}

char *getNumberOfListsInBox(App *app, char *id){
    SelectQuery result;
    char query[100];

    strcpy(query, "SELECT COUNT(id) FROM list WHERE id_box=");
    strcat(query, id);

    result = getSelectQuery(app, query);

    return result.listColumnsRows[0][0];
}
