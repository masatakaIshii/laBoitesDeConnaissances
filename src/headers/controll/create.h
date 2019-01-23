/*
** Filename : create.h
**
** Made by  : Masataka ISHII
**
** Description  : create menu functions for events
*/

#ifndef CONTROLL_CREATE_MODE
#include "../struct.h"
#include "../common.h"
#include "../model/boxModel.h"
#include "../view/create/createViewBoxes.h"

void createMode(App *app);
void createEventBoxes(App *app, SelectQuery *boxes, SDL_Event event, SDL_Rect *pageButtons, SDL_Rect *boxButtons, int *page);

#endif // CONTROLL_CREATE_MODE

