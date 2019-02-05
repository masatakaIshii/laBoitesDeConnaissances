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


typedef struct CreateButtons{
    SDL_Rect manageButtons[2];
    Uint8 manageColor[2][4];
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
    CreateInfo cInfo = loadCreateInfo(tableName, info);
    CreateButtons cButton = loadCreateButtons(app, tableName);
//    SDL_Rect pageButtons[2];
//    SDL_Rect manageButtons[2];
    SDL_Rect *boxButtons = NULL;
//    int nbOfBox = 0;
//    int page = 0;
//    int activeDel = 0;
    int done = 0;

    SelectQuery boxes = getBoxes(app);
    boxButtons = malloc(boxes.numberRows * sizeof(SDL_Rect));

    printf("cButton.colorTCreate.r : %d\n", cButton.colorTCreate.r);
    printf("cButton.colorTCreate.g : %d\n", cButton.colorTCreate.g);
    printf("cButton.colorTCreate.b : %d\n", cButton.colorTCreate.b);
    printf("cButton.colorTCreate.a : %d\n", cButton.colorTCreate.a);

    printf("cButton.colorTDelete.r : %d\n", cButton.colorTDelete.r);
    printf("cButton.colorTDelete.g : %d\n", cButton.colorTDelete.g);
    printf("cButton.colorTDelete.b : %d\n", cButton.colorTDelete.b);
    printf("cButton.colorTDelete.a : %d\n", cButton.colorTDelete.a);

    printf("cButton.rectCreate.x : %d\n", cButton.rectCreate.x);
    printf("cButton.rectCreate.y : %d\n", cButton.rectCreate.y);
    printf("cButton.rectCreate.w : %d\n", cButton.rectCreate.w);
    printf("cButton.rectCreate.h : %d\n", cButton.rectCreate.h);

    printf("cButton.rectCreate.x : %d\n", cButton.rectDelete.x);
    printf("cButton.rectCreate.y : %d\n", cButton.rectDelete.y);
    printf("cButton.rectCreate.w : %d\n", cButton.rectDelete.w);
    printf("cButton.rectCreate.h : %d\n", cButton.rectDelete.h);

    printf("cButton.manageColor[0][1] : %d\n", cButton.manageColor[0][1]);
    printf("cButton.manageColor[0][2] : %d\n", cButton.manageColor[0][2]);
    printf("cButton.manageColor[0][3] : %d\n", cButton.manageColor[0][3]);

    printf("cButton.manageColor[0][0] : %d\n", cButton.manageColor[0][0]);
    printf("cButton.manageColor[0][1] : %d\n", cButton.manageColor[0][1]);
    printf("cButton.manageColor[0][2] : %d\n", cButton.manageColor[0][2]);
    printf("cButton.manageColor[0][3] : %d\n", cButton.manageColor[0][3]);
    printf("cButton.manageColor[1][0] : %d\n", cButton.manageColor[1][0]);
    printf("cButton.manageColor[1][1] : %d\n", cButton.manageColor[1][1]);
    printf("cButton.manageColor[1][2] : %d\n", cButton.manageColor[1][2]);
    printf("cButton.manageColor[1][3] : %d\n", cButton.manageColor[1][3]);

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

CreateInfo loadCreateInfo(char* tableName, char **info){
    CreateInfo cInfo = {{0}, {0}, {0}, {0}, "", "", "", ""};

    strcpy(cInfo.tableName, tableName);

    if (strcmp(tableName, "box") == 0){
        loadCreateInfoBoxes(&cInfo);
    } else if (strcmp(tableName, "list") == 0 || strcmp(tableName, "card") == 0){
        loadCreateInfoLists(&cInfo, tableName, info);
    } else if (strcmp(tableName, "end") == 0){
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
        strcpy(cInfo->childTable, "end");
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

CreateButtons loadCreateButtons(App *app, char *tableName){
    CreateButtons cButtons;
    int i;

    for (i = 0; i < 2; i++){
        cButtons.manageButtons[i].h = 0;
        cButtons.manageButtons[i].w = 0;
        cButtons.manageButtons[i].x = 0;
        cButtons.manageButtons[i].y = 0;
    }
    if (strcmp(tableName, "box") == 0){
        getCButtonsManageColor(&cButtons, 0, app->colors.green);
    } else if (strcmp(tableName, "list") == 0){
        getCButtonsManageColor(&cButtons, 0, app->colors.yellow);
    } else if (strcmp(tableName, "card") == 0){
        getCButtonsManageColor(&cButtons, 0, app->colors.pink);
    } else if (strcmp(tableName, "end") == 0){
        getCButtonsManageColor(&cButtons, 0, app->colors.lightblue);
    }

    getCButtonsManageColor(&cButtons, 1, app->colors.red);
    cButtons.colorTCreate = app->colors.black;
    cButtons.colorTDelete = app->colors.black;

    initSDLRect(&cButtons.rectCreate);
    initSDLRect(&cButtons.rectDelete);

    cButtons.activeDel = 0;

    return cButtons;
}

void getCButtonsManageColor(CreateButtons *cButtons, int i, Uint8 *color){
    cButtons->manageColor[i][0] = color[0];
    cButtons->manageColor[i][1] = color[1];
    cButtons->manageColor[i][2] = color[2];
    cButtons->manageColor[i][3] = color[3];
}

void initSDLRect(SDL_Rect *rect){
    rect->h = 0;
    rect->w = 0;
    rect->x = 0;
    rect->y = 0;
}
