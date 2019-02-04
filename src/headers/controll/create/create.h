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
    SDL_Color manageColor[2];
    int activeDel;
}CreateButtons;

typedef struct CreatePage{
    SDL_Rect *boxButtons;
    SDL_Color mainPColor;
    int nbOfBox;
    SDL_Color pageBColor;
    SDL_Rect pageButtons[2];
    int page;
}CreatePage;

void createMode(App *app, char *tableName, char **info);
void createEventBoxes(App *app, SelectQuery *boxes, SDL_Event event, SDL_Rect *pageButtons, SDL_Rect *boxButtons, SDL_Rect *manageButtons, int *page, int *activeDel);
void getTitleDeTailDate(CreateInfo *cInfo, char* tableName, char **info);

CreateInfo loadCreateInfo(App *app, char* tableName, char **info);
void loadCreateInfoBoxes(CreateInfo *cInfo);
void loadCreateInfoLists(CreateInfo *cInfo, char *tableName, char **info);
void loadCreateInfoShowCards(CreateInfo *cInfo, char **info);

#endif // CONTROLL_CREATE_MODE

