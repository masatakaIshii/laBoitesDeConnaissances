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
    CreateButtons cButtons = loadCreateButtons(app, tableName);
    SelectQuery elements;
    CreatePage cPages;
    int done = 0;
    int checkEnd = strcmp(tableName, "end");

    if (checkEnd != 0){
        elements = getSelectedTable(app, tableName, info);
        cPages = loadCreatePage(app, tableName, elements.numberRows);
    }

    while(!done) {
        SDL_WaitEvent(&event);
        commonEvents(app, event, &done);
        switch (event.type) {
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    if (checkEnd){
                        createEventElements(app, &elements, &event, &cInfo, &cButtons, &cPages);
                    } else {
                        //createEventShowCard(app, &cInfo);
                    }
                    //
                }
        }
        if (checkEnd != 0 ){
            displayElements(app, &elements, &cInfo, &cButtons, &cPages, tableName);
        } else {
            displayCard(app, &cInfo, &cButtons);
        }
    }

    if (checkEnd != 0){
        quitCPages(&cPages);
        quitSelectQuery(&elements);
    }
}

CreateInfo loadCreateInfo(char* tableName, char **info){
    CreateInfo cInfo = {{0}, {0}, {0}, {0}, {0}, "", "", "", "", "", ""};

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
    strcpy(cInfo->question, "");
    strcpy(cInfo->answer, "");
    strcpy(cInfo->datetime, "");
    strcpy(cInfo->childTable, "list");
}

void loadCreateInfoLists(CreateInfo *cInfo, char *tableName, char **info){
    char yearMonthDate[MAX_VARCHAR];
    char hoursMinutesSec[MAX_VARCHAR];

    sprintf(cInfo->title, "This is the '%s' %s !", info[1], (strcmp(tableName, "list") == 0) ? "box" : "list");

    if (strcmp(tableName, "list") == 0){
        strcpy(cInfo->childTable, "card");
        sscanf(info[3], "%s %s", yearMonthDate, hoursMinutesSec);
    } else {
        sscanf(info[3], "%s %s", yearMonthDate, hoursMinutesSec);
        strcpy(cInfo->childTable, "end");
    }

    strcpy(cInfo->question, "");
    strcpy(cInfo->answer, "");

    sprintf(cInfo->datetime, "Last modification : %s at %s", yearMonthDate, hoursMinutesSec);
}

void loadCreateInfoShowCards(CreateInfo *cInfo, char **info){
    char yearMonthDate[MAX_VARCHAR];
    char hoursMinutesSec[MAX_VARCHAR];

    sprintf(cInfo->title, "The name of card is : %s", info[1]);
    sprintf(cInfo->question, "The question is : %s", info[3]);
    sprintf(cInfo->answer, "The answer is : %s", info[4]);
    sscanf(info[8], "%s %s", yearMonthDate, hoursMinutesSec);
    sprintf(cInfo->datetime, "Last modification : %s at %s", yearMonthDate, hoursMinutesSec);
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
    verifyPointer(app, cPage.elementButtons, "Problem malloc cPage.elementButtons in loadCreatePage\n");
    cPage.elementName = malloc(sizeof(SDL_Rect) * numberRows);
    verifyPointer(app, cPage.elementName, "Problem malloc cPage.elementName in loadCreatePage\n");
    cPage.elementDate = malloc(sizeof(SDL_Rect) * numberRows);
    verifyPointer(app, cPage.elementDate, "Problem malloc cPage.elementDate in loadCreatePage\n");

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

    //renderText()

    cPage.nbTotalElements = numberRows;
    cPage.page = 0;

    return cPage;
}

void getCPageColors(App *app, CreatePage *cPage, char *tableName){
    if (strcmp(tableName, "box") == 0){
        getCPageMainAndPageColors(cPage, app->colors.blue, app->colors.green);
        cPage->indexDate = 4;
    } else if (strcmp(tableName, "list") == 0){
        getCPageMainAndPageColors(cPage, app->colors.blue, app->colors.yellow);
        cPage->indexDate = 4;
    } else if (strcmp(tableName, "card") == 0){
        getCPageMainAndPageColors(cPage, app->colors.blue, app->colors.pink);
        cPage->indexDate = 8;
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

void quitCPages(CreatePage *cPages){
    free(cPages->elementButtons);
    free(cPages->elementDate);
    free(cPages->elementName);
}
