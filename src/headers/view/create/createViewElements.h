/*
** Filename : createViewElements.h
**
** Made by  : Masataka ISHII
**
** Description  : view elements functions
*/

#ifndef CREATE_VIEW_BOXES
#include "../../struct.h"
#include "../../common.h"
#include "../commonView.h"

void displayBoxes(App *app, int page, SDL_Rect *pageButtons, SDL_Rect *boxButtons, SDL_Rect *manageButtons, int *nbOfBox, int nbTotalOfBox);

int createCustumElementsPage(App *app, SelectQuery *elements, CreateButtons *cButtons, CreatePage *cPages, DisplayManager display);
void fillSizePosColor(App *app, SDL_Rect *rectToFill, int w, int h, int x, int y, Uint8 *color);
void displayCard (App *app, CreateInfo *cInfo,CreateButtons *cButtons);
void displayElementsInfos(App *app, SelectQuery *elements, CreatePage *cPages, Position *pos, DisplayManager display, int i, TextRender *tRender, int y, int x);
int getAppropriateXOrY(int lengthChild, int lengthParent, int posParent);
void displayPageButtons(App *app, CreatePage *cPage, int nbElements);

void renderTextToPageButtons(App *app, TextRender *textRender, SDL_Rect pageButton, char *text);

void displayCard (App *app, CreateInfo *cInfo,CreateButtons *cButtons);

#endif // CREATE_VIEW_BOXES


