/*
** Filename : createViewElements.h
**
** Made by  : Masataka ISHII
**
** Description  : view elements functions
*/

#ifndef CREATE_VIEW_BOXES
#include <ctype.h>
#include "../../struct.h"
#include "../../common.h"
#include "../commonView.h"

typedef void(*showCard)(App*, CreateInfo*, int, int, int);

void displayElements(App *app, SelectQuery *elements, CreateInfo *cInfo, CreateButtons *cButtons, CreatePage *cPages, char *tableName);
void displayElementInfo(App *app, CreateInfo *cInfo, char *tableName);
void displayBoxInfo(App *app, CreateInfo *cInfo);
void displayListOrCard(App *app, CreateInfo *cInfo);

void putButtonsUpperName(CreateButtons *cButtons, char *tableName, char *buttonsText0, char *buttonsText1);

int createCustumElementsPage(App *app, SelectQuery *elements, CreateButtons *cButtons, CreatePage *cPages, DisplayManager display);
void fillSizePosColor(App *app, SDL_Rect *rectToFill, int w, int h, int x, int y, Uint8 *color);
void displayCard (App *app, CreateInfo *cInfo,CreateButtons *cButtons);
void displayElementsInfos(App *app, SelectQuery *elements, CreatePage *cPages, Position *pos, DisplayManager display, int i, TextRender *tRender, int y, int x);
int getAppropriateXOrY(int lengthChild, int lengthParent, int posParent);
void displayPageButtons(App *app, CreatePage *cPage, int nbElements);

void renderTextToButtons(App *app, TextRender *textRender, SDL_Rect button, char *text, double coefW, double coefH, SDL_Color color);

void displayManageButtons(App *app, CreateButtons *cButtons);

void displayCard (App *app, CreateInfo *cInfo,CreateButtons *cButtons);
void displayTitleCard(App *app, CreateInfo *cInfo, int h, int w, int y);
void displayQuestionCard(App *app, CreateInfo *cInfo, int h, int w, int y);
void displayAnswerCard(App *app, CreateInfo *cInfo, int h, int w, int y);
void displayDateTimeCard(App *app, CreateInfo *cInfo, int h, int w, int y);

#endif // CREATE_VIEW_BOXES


