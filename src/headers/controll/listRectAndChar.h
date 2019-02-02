/*
** Filename : listRectAndChar.h
**
** Made by  : Masataka ISHII
**
** Description  : function concern to chained list
*/


#ifndef LIST_RECT_AND_CHAR
#include "stdio.h"
#include "stdlib.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "../struct.h"
#include "../common.h"

ListInputText *addListInputTextInEnd(App *app, SDL_Rect *rect, char *newChar, ListInputText *list);
ListInputText *deleteEndTextInput(ListInputText *list, int *sizeOfChar);
ListInputText *deleteFrontListInputText(ListInputText *start);
ListInputText *deleteAllListInputText(ListInputText *list);

void showListInputText(ListInputText *list);
#endif // LIST_RECT_AND_CHAR

