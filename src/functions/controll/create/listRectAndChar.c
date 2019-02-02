/*
** Filename : listRectAndChar.c
**
** Made by  : Masataka ISHII
**
** Description  : function concern to chained list for structure ListInputText
*/

#include "../../../headers/controll/listRectAndChar.h"

/**
*Add new character in list the end of the list
*
*
*
*/
ListInputText *addListInputTextInEnd(App *app, SDL_Rect *rect, char *newChar, ListInputText *list){
    ListInputText *temp;
    ListInputText *newEnd = malloc(sizeof(ListInputText));
    verifyPointer(app, newEnd, "Problem malloc newEnd in addListInputTextInEnd");

    if (rect != NULL){
        newEnd->inputChar.charRect.h = rect->h;
        newEnd->inputChar.charRect.w = rect->w;
        newEnd->inputChar.charRect.x = rect->x;
        newEnd->inputChar.charRect.y = rect->y;
    }

    strcpy(newEnd->inputChar.oneChar, newChar);

    newEnd->next = NULL;
    if (list == NULL) {
        return newEnd;
    }

    temp = list;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newEnd;

    return list;
}

ListInputText *deleteEndTextInput(ListInputText *list, int *sizeOfChar) {
    if (list == NULL) {
        return NULL;
    }

    if (list->next == NULL) {
        *sizeOfChar = strlen(list->inputChar.oneChar);
        free(list);
        return NULL;
    }
    ListInputText *temp = list;
    ListInputText *pTemp = list;

    while (temp->next != NULL) {
        pTemp = temp;
        temp = temp->next;
    }
    *sizeOfChar = strlen(temp->inputChar.oneChar);

    free(temp);

    pTemp->next = NULL;

    return list;
}

ListInputText *deleteFrontListInputText(ListInputText *start){
    ListInputText *item = start;

    if (item != NULL){
        start = start->next;
        free(item);
    }

    return start;
}

ListInputText *deleteAllListInputText(ListInputText *list){
    while(list != NULL){
        list = deleteFrontListInputText(list);
    }

    return NULL;
}

void showListInputText(ListInputText *list) {
    ListInputText *temp = list;

    while(temp != NULL) {
        printf("inputChar.oneChar : %s, ", temp->inputChar.oneChar);
        printf("inputChar.charRect.h : %d, ", temp->inputChar.charRect.h);
        printf("inputChar.charRect.w : %d, ", temp->inputChar.charRect.w);
        printf("inputChar.charRect.x : %d, ", temp->inputChar.charRect.x);
        printf("inputChar.charRect.y : %d\n", temp->inputChar.charRect.y);
        temp = temp->next;
    }
}
