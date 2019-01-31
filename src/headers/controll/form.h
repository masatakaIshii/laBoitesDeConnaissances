/*
** Filename : form.c
**
** Made by  : Masataka ISHII
**
** Description  : form functions for events
*/

#ifndef CREATE_FORM
#include "../struct.h"
#include "../model/formModel.h"
#include "listRectAndChar.h"
#include "textInput.h"

void createForm(App *app, SelectQuery *table, SDL_Rect *listButton, char *tableName, int idParent);
void displayInput(App *app, TextsInput *input);
int adaptWForTexts(int wOneChar, int nbChar);

#endif // CREATE_FORM

