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
#include "../../view/create/createViewBoxes.h"
#include "../../model/createModel.h"
#include "../../model/modelHelper/modelShow.h"
#include "form.h"

typedef struct CreateInfo{
    SDL_Rect titleRect;
    SDL_Rect detailRect;
    SDL_Rect dateRect;
    SDL_Color textColor;
    char tableName[MAX_VARCHAR];
    char title[MAX_VARCHAR];
    char detail[MAX_VARCHAR];
    char datetime[MAX_VARCHAR];
    char childTable[MAX_VARCHAR];
}CreateInfo;

typedef struct CreateButtons{
    SDL_Rect manageButtons[2];
    SDL_Rect rectCreate;
    SDL_Rect rectDelete;
    Uint8 manageColor[2][4];
    SDL_Color colorTCreate;
    SDL_Color colorTDelete;
    int activeDel;
}CreateButtons;

typedef struct CreatePage{
    SDL_Rect *elementButtons;
    Uint8 mainPColor[4];
    int nbOfBox;
    Uint8 pageBColor[4];
    SDL_Rect pageButtons[2];
    char next[MAX_VARCHAR];
    char before[MAX_VARCHAR];
    int page;
}CreatePage;

void createMode(App *app, char *tableName, char **info);
void createEventBoxes(App *app, SelectQuery *boxes, SDL_Event event, SDL_Rect *pageButtons, SDL_Rect *boxButtons, SDL_Rect *manageButtons, int *page, int *activeDel);
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
#endif // CONTROLL_CREATE_MODE

