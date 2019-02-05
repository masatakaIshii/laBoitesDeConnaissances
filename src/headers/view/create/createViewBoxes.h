/*
** Filename : createViewBoxes.h
**
** Made by  : Baptiste LEGO, Masataka ISHII
**
** Description  : view boxes functions
*/

#ifndef CREATE_VIEW_BOXES
#include "../../struct.h"
#include "../../common.h"
#include "../commonView.h"
#include "../../controll/create/create.h"

void displayBoxes(App *app, int page, SDL_Rect *pageButtons, SDL_Rect *boxButtons, SDL_Rect *manageButtons, int *nbOfBox, int nbTotalOfBox);

int createCustumElementsPage(App *app, CreateButtons *cButtons, CreatePage *cPages, DisplayManager display);
void fillSizePosColor(App *app, SDL_Rect *rectToFill, int w, int h, int x, int y, Uint8 *color);
void displayCard (App *app, CreateInfo *cInfo,CreateButtons *cButtons);

#endif // CREATE_VIEW_BOXES


