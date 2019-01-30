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
    char query[150];
    char id[4];

    sprintf(id, "%d", listId);
    strcpy(query, "SELECT id, name, created_date, question, answer, id_list, count, UNIX_TIMESTAMP(validated_date), modified_date FROM card WHERE id_list=");
    strcat(query, id);

    return getSelectQuery(app, query);
}
