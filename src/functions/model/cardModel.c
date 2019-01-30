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
#include "../../headers/model/modelHelper/modelIUD.h"

SelectQuery getCardsFromList(App *app, int listId){
    char query[150];
    char id[4];

    sprintf(id, "%d", listId);
    strcpy(query, "SELECT id, name, created_date, question, answer, id_list, count, UNIX_TIMESTAMP(validated_date), modified_date FROM card WHERE id_list=");
    strcat(query, id);

    return getSelectQuery(app, query);
}

int resetCards(App *app, int listId){
    char query[100];
    char id[4];

    sprintf(id, "%d", listId);
    strcpy(query, "UPDATE card SET count = 0 WHERE id_list = ");
    strcat(query, id);

    return queryIUD(app, query);
}

int setNewCardValidation(App *app, char *cardId){
    char query[100];

    strcpy(query, "UPDATE card SET count = count + 1, validated_date = NOW() WHERE id = ");
    strcat(query, cardId);

    return queryIUD(app, query);
}
