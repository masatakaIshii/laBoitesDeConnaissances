/*
** Filename : create.h
**
** Made by  : Masataka ISHII
**
** Description  : create menu functions for events
*/

#ifndef CONTROLL_CREATE_MODE
#include "../../struct.h"
#include "../../common.h"
#include "../../model/boxModel.h"

#include "../../model/createModel.h"
#include "../../model/modelHelper/modelShow.h"

void createMode(App *app, char *tableName, char **info);
//void createEventElements(App *app, SelectQuery *elements, SDL_Event event, CreateInfo *cInfo, CreateButtons *cButton, CreatePage *cPages);
void getTitleDeTailDate(CreateInfo *cInfo, char* tableName, char **info);

CreateInfo loadCreateInfo(char* tableName, char **info);
void loadCreateInfoBoxes(CreateInfo *cInfo);
void loadCreateInfoLists(CreateInfo *cInfo, char *tableName, char **info);
void loadCreateInfoShowCards(CreateInfo *cInfo, char **info);

CreateButtons loadCreateButtons(App *app, char *tableName);
void getCButtonsManageColor(CreateButtons *cButtons, int i, Uint8 *color);
void initSDLRect(SDL_Rect *rect);

CreatePage loadCreatePage(App *app, char *tableName, int numberRows);
void getCPageColors(App *app, CreatePage *cPage, char *tableName);
void getCPageMainAndPageColors(CreatePage *cPage, Uint8 *color1, Uint8 *color2);
void quitCPages(CreatePage *cPages);
#endif // CONTROLL_CREATE_MODE

