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

typedef struct Create{
    char tableName[MAX_VARCHAR];
    char title;
    SDL_Rect titleRect;
    SDL_Color textColor;
    char childTable[MAX_VARCHAR];
}Create;

typedefStruct CreateButtons{
    SDL_Rect manageButtons[2];
    SDL_Rect pageButtons[2];
    SDL_Color manageColor[2];
    SDL_Color pageBColor;
    int activeDel;
}CButtons;

typeDefStruct CreatePage{
    SDL_Rect *boxButtons;
    int nbOfBox;
    int page;
}CreatePage;
*
*/

void createMode(App *app, char *tableName) {
    SDL_Event event;
    SDL_Rect pageButtons[2];
    SDL_Rect *boxButtons = NULL;
    SDL_Rect manageButtons[2];
    int nbOfBox = 0;
    int page = 0;
    int done = 0;
    int activeDel = 0;

    SelectQuery boxes = getBoxes(app);
    boxButtons = malloc(boxes.numberRows * sizeof(SDL_Rect));

    while(!done) {
        SDL_WaitEvent(&event);
        commonEvents(app, event, &done);
        switch (event.type) {
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    createEventBoxes(app, &boxes, event, pageButtons, boxButtons, manageButtons, &page, &activeDel);
                }
        }
        displayBoxes(app, page, pageButtons, boxButtons, manageButtons, &nbOfBox, boxes.numberRows);
    }

    free(boxButtons);
    quitSelectQuery(boxes);
}

createEventBoxes(App *app, SelectQuery *boxes, SDL_Event event, SDL_Rect *pageButtons, SDL_Rect *boxButtons, SDL_Rect *manageButtons, int *page, int *activeDel) {
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
