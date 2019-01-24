/*
** Filename : create.c
**
** Made by  : Masataka ISHII
**
** Description  : create menu functions for events
*/
#include "../../../headers/controll/create.h"

void createMode(App *app) {
    SDL_Event event;
    SDL_Rect pageButtons[2];
    SDL_Rect *boxButtons = NULL;
    SDL_Rect manageButtons[2];
    int nbOfBox = 0;
    int page = 0;
    int done = 0;

    SelectQuery boxes = getBoxes(app);
    boxButtons= malloc(boxes.numberRows * sizeof(SDL_Rect));

    while(!done) {
        SDL_WaitEvent(&event);
        commonEvents(app, event, &done);
        switch (event.type) {
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    createEventBoxes(app, &boxes, event, pageButtons, boxButtons, manageButtons, &page);
                }
        }
        displayBoxes(app, page, pageButtons, boxButtons, manageButtons, &nbOfBox, boxes.numberRows);
    }

    free(boxButtons);
}

void createEventBoxes(App *app, SelectQuery *boxes, SDL_Event event, SDL_Rect *pageButtons, SDL_Rect *boxButtons, SDL_Rect *manageButtons, int *page) {
    int i;
    int currentId = (*page) * boxes->numberFields;
    // Change the page
    if (inRect(pageButtons[0], event.button.x, event.button.y)) {
        (*page)--;
    } else if(inRect(pageButtons[1], event.button.x, event.button.y)) {
        (*page)++;
    }

    if (inRect(manageButtons[0], event.button.x, event.button.y)) {
        createForm(app, boxes, boxButtons, "box");
    }
    if (inRect(manageButtons[1], event.button.x, event.button.y)) {
        //deleteBoxForm
        printf("deleBoxForm\n");
    }

    for (i = currentId ; i < (currentId + boxes->numberFields); i++) {
        if (inRect(boxButtons[i], event.button.x, event.button.y)){
            //createModeList(app, boxes, page, i);
            printf("boxes : %d => %s : %s\n", i, boxes->listColumnsRows[i][0], boxes->listColumnsRows[i][1]);
        }
    }
}
