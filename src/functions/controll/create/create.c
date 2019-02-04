/*
** Filename : create.c
**
** Made by  : Masataka ISHII
**
** Description  : create menu functions for events
*/
#include "../../../headers/controll/create/create.h"

/**
*@todo : define structure to manage page :

typedef struct CreateInfo{
    char tableName[MAX_VARCHAR];
    char title[MAX_VARCHAR];
    SDL_Rect titleRect;
    char detail[MAX_VARCHAR];
    SDL_Rect detailRect;
    char datetime[MAX_VARCHAR];
    SDL_Color textColor;
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
*
*/

void createMode(App *app, char *tableName, char **info) {
    SDL_Event event;

    printf("tableName : %s\n", tableName);
    CreateInfo cInfo = loadCreateInfo(app, tableName, info);
//    SDL_Rect pageButtons[2];
//    SDL_Rect manageButtons[2];
    SDL_Rect *boxButtons = NULL;
//    int nbOfBox = 0;
//    int page = 0;
//    int activeDel = 0;
    int done = 0;

    SelectQuery boxes = getBoxes(app);
    boxButtons = malloc(boxes.numberRows * sizeof(SDL_Rect));

    printf("cInfo.childTable  : %s\n", cInfo.childTable);
    printf("cInfo.datetime : %s\n", cInfo.datetime);
    printf("cInfo.detail : %s\n", cInfo.detail);
    printf("cInfo.tableName : %s\n", cInfo.tableName);
    printf("cInfo.title : %s\n", cInfo.title);
    printf("cInfo.childTable : %s\n", cInfo.childTable);
    printf("cInfo.dateRect.h : %d\n", cInfo.dateRect.h);
    printf("cInfo.detailRect.w : %d\n", cInfo.detailRect.w);
    printf("cInfo.titleRect.y : %d\n", cInfo.titleRect.y);
    printf("cInfo.textColor.r : %d\n", cInfo.textColor.r);

    while(!done) {
        SDL_WaitEvent(&event);
        commonEvents(app, event, &done);
        switch (event.type) {
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    //createEventBoxes(app, &boxes, event, pageButtons, boxButtons, manageButtons, &page, &activeDel);
                }
        }
//        displayBoxes(app, page, pageButtons, boxButtons, manageButtons, &nbOfBox, boxes.numberRows);
    }

    //free(boxButtons);
    quitSelectQuery(&boxes);
}

void createEventBoxes(App *app, SelectQuery *boxes, SDL_Event event, SDL_Rect *pageButtons, SDL_Rect *boxButtons, SDL_Rect *manageButtons, int *page, int *activeDel) {
    int i;
    int currentId = (*page) * boxes->numberFields;
    int check = 0;
    // Change the page
    if (inRect(pageButtons[0], event.button.x, event.button.y)) {
        (*page)--;
    } else if(inRect(pageButtons[1], event.button.x, event.button.y)) {
        (*page)++;
    }

    if (inRect(manageButtons[0], event.button.x, event.button.y)) {
        check = createForm(app, boxes, boxButtons, "box", 0);
        if(check == 1){

        }
    }
    if (inRect(manageButtons[1], event.button.x, event.button.y)) {

    }

    for (i = currentId ; i < (currentId + boxes->numberFields); i++) {
        if (inRect(boxButtons[i], event.button.x, event.button.y)){
            //createModeList(app, boxes->listColumnsRows[i]);
        }
    }
}

CreateInfo loadCreateInfo(App *app, char* tableName, char **info){
    CreateInfo cInfo = {{0}, {0}, {0}, {0}, "", "", "", ""};

    strcpy(cInfo.tableName, tableName);

    if (strcmp(tableName, "box") == 0){
        loadCreateInfoBoxes(&cInfo);
    } else if (strcmp(tableName, "list") == 0 || strcmp(tableName, "card") == 0){
        loadCreateInfoLists(&cInfo, tableName, info);
    } else if (strcmp(tableName, "") == 0){
        loadCreateInfoShowCards(&cInfo, info);
    } else {

    }

    return cInfo;
    //initCreateRect(&cInfo);
}

void loadCreateInfoBoxes(CreateInfo *cInfo){
    strcpy(cInfo->title, "Welcome to the create mode !");
    strcpy(cInfo->detail, "This is all boxes in create mode !");
    strcpy(cInfo->datetime, "");
    strcpy(cInfo->childTable, "list");
}

void loadCreateInfoLists(CreateInfo *cInfo, char *tableName, char **info){
    char yearMonthDate[MAX_VARCHAR];
    char hoursMinutesSec[MAX_VARCHAR];

    sprintf(cInfo->title, "This is the '%s' %s !", info[1], (strcmp(tableName, "list") == 0) ? "box" : "list");
    sprintf(cInfo->detail, "Description : %s", info[2]);

    if (strcmp(tableName, "list") == 0){
        strcpy(cInfo->childTable, "card");
        sscanf(info[4], "%s %s", yearMonthDate, hoursMinutesSec);
    } else {
        sscanf(info[8], "%s %s", yearMonthDate, hoursMinutesSec);
        strcpy(cInfo->childTable, "");
    }

    sprintf(cInfo->datetime, "Last modification the %s at %s", yearMonthDate, hoursMinutesSec);
}

void loadCreateInfoShowCards(CreateInfo *cInfo, char **info){
    char yearMonthDate[MAX_VARCHAR];
    char hoursMinutesSec[MAX_VARCHAR];

    sprintf(cInfo->title, "The question is : %s", info[3]);
    sprintf(cInfo->detail, "The answer is : %s", info[4]);
    sscanf(info[4], "%s %s", yearMonthDate, hoursMinutesSec);
    sprintf(cInfo->datetime, "Last modification the %s at %s", yearMonthDate, hoursMinutesSec);
    strcpy(cInfo->childTable, "");
}

//void initCreateRect(CreateInfo *cInfo){
//
//    cInfo->dateRect.h = 0;
//    cInfo->dateRect.w = 0;
//    cInfo->dateRect.x = 0;
//    cInfo->dateRect.y = 0;
//
//    cInfo->detailRect.h = 0;
//    cInfo->detailRect.w = 0;
//    cInfo->detailRect.x = 0;
//    cInfo->detailRect.y = 0;
//
//    cInfo->titleRect.h = 0;
//    cInfo->titleRect.w = 0;
//    cInfo->titleRect.x = 0;
//    cInfo->titleRect.y = 0;
//
//    cInfo->textColor.a = 0;
//    cInfo->textColor.w = 0;
//    cInfo->textColor.x = 0;
//    cInfo->textColor.y = 0;
//}
