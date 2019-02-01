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
#include "../view/create/createViewForm.h"

void createForm(App *app, SelectQuery *table, SDL_Rect *listButton, char *tableName, int idParent);;
int eventForm(App *app, SDL_Event *event, int *done);

ListFields getListFieldsForForm(App *app, MySqlTable tableInfo);
int *adaptedIndexesToForm(App *app, MySqlTable tableInfo, int *numberField);
int *addIndexInArray(App *app, int *indexes, int index, int numberField);

#endif // CREATE_FORM

