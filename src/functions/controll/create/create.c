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
    SDL_Rect *elementButtons;
    Uint8 mainPColor[4];
    int nbOfBox;
    Uint8 pageBColor[4];
    SDL_Rect pageButtons[2];
    char next[MAX_VARCHAR];
    char before[MAX_VARCHAR];
    int page;
}CreatePage;
*
*/

void createMode(App *app, char *tableName, char **info) {
    SDL_Event event;
    printf("tableName : %s\n", tableName);
    CreateInfo cInfo = loadCreateInfo(tableName, info);
    CreateButtons cButton = loadCreateButtons(app, tableName);
    SelectQuery elements;
    CreatePage cPage;

    int checkEnd = strcmp(tableName, "end");
    if (checkEnd != 0){
        elements = getSelectedTable(app, tableName);
        cPage = loadCreatePage(app, tableName, elements.numberRows);

        int i;
        for (i = 0; i < elements.numberRows; i++){
            printf("cPage.elementButtons[%d].h : %d\n", i, cPage.elementButtons[i].h);
            printf("cPage.elementButtons[%d].w : %d\n", i, cPage.elementButtons[i].w);
            printf("cPage.elementButtons[%d].x : %d\n", i, cPage.elementButtons[i].x);
            printf("cPage.elementButtons[%d].y : %d\n", i, cPage.elementButtons[i].y);
        }
        printf("cPage.page : %d\n", cPage.page);

        for (i = 0; i < 4; i++){
            printf("cPage.mainPColor{%d] : %d\n", i, cPage.mainPColor[i]);
        }

        for (i = 0; i < 4; i++){
            printf("cPage.pageBColor[%d] : %d\n", i, cPage.pageBColor[i]);
        }

        printf("cPage.nbOfBox : %d\n", cPage.nbOfBox);

        for (i = 0; i < 2; i++){
            printf("cPage.pageButtons[%d].h : %d\n", i, cPage.pageButtons[i].h);
            printf("cPage.pageButtons[%d].w : %d\n", i, cPage.pageButtons[i].w);
            printf("cPage.pageButtons[%d].x : %d\n", i, cPage.pageButtons[i].x);
            printf("cPage.pageButtons[%d].y : %d\n", i, cPage.pageButtons[i].y);
        }

        printf("cPage.next : %s\n", cPage.next);
        printf("cPage.before : %s\n", cPage.before);
    }


    //SDL_Rect *boxButtons = NULL;
//    int nbOfBox = 0;
//    int page = 0;
//    int activeDel = 0;
    int done = 0;
    //boxButtons = malloc(boxes.numberRows * sizeof(SDL_Rect));

//    printf("elements.numberFields : %d\n", elements.numberFields);
//    int i;
//    for (i =0; i < elements.numberFields; i++){
//        printf("elements.numberFields : %s\n", elements.listFields[i]);
//    }
//
//    printf("numberRows : %d\n", elements.numberRows);
//    showQueryResult(app, &elements);
//
//
//    for (i = 0; i < 7; i++){
//        printf("info[%d] : %s\n", i, info[i]);
//    }

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

    if (checkEnd != 0){
        free(cPage.elementButtons);
        quitSelectQuery(&elements);
    }
    //free(boxButtons);

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
        sscanf(info[4], "%s %s", yearMonthDate, hoursMinutesSec);
        strcpy(cInfo->childTable, "end");
    }

    sprintf(cInfo->datetime, "Last modification the %s at %s", yearMonthDate, hoursMinutesSec);
}

void loadCreateInfoShowCards(CreateInfo *cInfo, char **info){
    char yearMonthDate[MAX_VARCHAR];
    char hoursMinutesSec[MAX_VARCHAR];

    sprintf(cInfo->title, "The question is : %s", info[3]);
    sprintf(cInfo->detail, "The answer is : %s", info[4]);
    sscanf(info[8], "%s %s", yearMonthDate, hoursMinutesSec);
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

CreatePage loadCreatePage(App *app, char *tableName, int numberRows){
    CreatePage cPage;
    int i;

    cPage.elementButtons = malloc(sizeof(SDL_Rect) * numberRows);

    for (i = 0; i < numberRows; i++){
        cPage.elementButtons[i].h = 0;
        cPage.elementButtons[i].w = 0;
        cPage.elementButtons[i].x = 0;
        cPage.elementButtons[i].y = 0;
    }
    getCPageColors(app, &cPage, tableName);

    initSDLRect(&cPage.pageButtons[0]);
    initSDLRect(&cPage.pageButtons[1]);

    strcpy(cPage.before, "before");
    strcpy(cPage.next, "next");

    cPage.nbOfBox = 0;
    cPage.page = 0;

    return cPage;
}

void getCPageColors(App *app, CreatePage *cPage, char *tableName){
    if (strcmp(tableName, "box") == 0){
        getCPageMainAndPageColors(cPage, app->colors.blue, app->colors.green);
    } else if (strcmp(tableName, "list") == 0){
        getCPageMainAndPageColors(cPage, app->colors.green, app->colors.yellow);
    } else if (strcmp(tableName, "card") == 0){
        getCPageMainAndPageColors(cPage, app->colors.yellow, app->colors.pink);
    } else {

    }
}

void getCPageMainAndPageColors(CreatePage *cPage, Uint8 *color1, Uint8 *color2){
    cPage->mainPColor[0] = color1[0];
    cPage->mainPColor[1] = color1[1];
    cPage->mainPColor[2] = color1[2];
    cPage->mainPColor[3] = color1[3];

    cPage->pageBColor[0] = color2[0];
    cPage->pageBColor[1] = color2[1];
    cPage->pageBColor[2] = color2[2];
    cPage->pageBColor[3] = color2[3];
}
