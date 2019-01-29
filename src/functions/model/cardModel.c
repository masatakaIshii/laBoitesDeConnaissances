/*
** Filename : cardModel.c
**
** Made by  : Baptiste LEGO
**
** Description  : getting data for card table
*/

#include <stdlib.h>
#include <stdio.h>
#include "../../headers/model/modelHelper/modelSelect.h"

SelectQuery getCardsFromList(App *app, int listId){
    char query[50];
    char id[4];

    sprintf(id, "%d", listId);
    strcpy(query, "SELECT * from card WHERE id_list=");
    strcat(query, id);

    return getSelectQuery(app, query);
}
