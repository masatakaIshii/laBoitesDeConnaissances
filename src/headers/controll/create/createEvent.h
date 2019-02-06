/*
** Filename : createEvent.h
**
** Made by  : Masataka ISHII
**
** Description  : create menu functions for events
*/

#ifndef CREATE_EVENT

#include "../../struct.h"
#include "../../common.h"
#include "form.h"

int createEventElements(App *app, SelectQuery *elements, SDL_Event *event, CreateInfo *cInfo, CreateButtons *cButton, CreatePage *cPages, char *tableName);

void createPageEvent(App *app, SDL_Event *event, CreateButtons *cButton, CreatePage *cPages);
#endif // CREATE_EVENT
