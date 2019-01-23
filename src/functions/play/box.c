/*
** Filename : box.c
**
** Made by  : Baptiste LEGO
**
** Description  : play mode main functions
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "../../headers/common.h"
#include "../../headers/play/box.h"
#include "../../headers/play/list.h"
#include "../../headers/model/boxModel.h"

void playMode(App *app){
    SDL_Event event;
    SDL_Rect pageButtons[2];
    SDL_Rect *boxButtons = NULL;
    int nbOfBox = 0;
    int nbTotalOfBox = 0;
    int page = 0;
    int done = 0;
    int i = 0;

    // Getting data
    SelectQuery boxes = getBoxes(app);
    nbTotalOfBox = boxes.numberRows;
    boxButtons = malloc(nbTotalOfBox * sizeof(SDL_Rect));

    // Event loop
    while (!done) {
        SDL_WaitEvent(&event);
        commonEvents(app, event, &done);
        switch (event.type) {
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT){
                    // Change the page
                    if(inRect(pageButtons[0] , event.button.x, event.button.y))
                        page--;
                    else if(inRect(pageButtons[1] , event.button.x, event.button.y))
                        page++;

                    // Display a box
                    for(i = 0; i < nbOfBox; i++){
                        if(inRect(boxButtons[i], event.button.x, event.button.y))
                            listMenu(app, boxes, page, i);
                    }
                }
            break;
        }

        displayHomePlay(app, page, pageButtons, boxButtons, &nbOfBox, nbTotalOfBox);
    }

    free(boxButtons);
}


////////////////////////// DISPLAY \\\\\\\\\\\\\\\\\\\\\\\\\\_


void displayHomePlay(App *app, int page, SDL_Rect *pageButtons, SDL_Rect *boxButtons, int *nbOfBoxInPage, int nbTotalOfBox){
    SDL_Rect nullBtn = {0};

    // Set background color
    SDL_SetRenderDrawColor(app->renderer, app->colors.blue[0], app->colors.blue[1], app->colors.blue[2], app->colors.blue[3]);
    SDL_RenderClear(app->renderer);

    // Creating boxes
    *nbOfBoxInPage = createBoxPage(app, boxButtons, nbTotalOfBox, page);

    // Conditions for page buttons
    if(page != 0)
        pageButtons[0] = createRect(app, app->config.height / 12, app->config.height / 24, (app->config.width / 12) * 5, (app->config.height / 12) * 11, app->colors.green);
    else
        pageButtons[0] = nullBtn;

    if(10 * (page+1) < nbTotalOfBox)
        pageButtons[1] = createRect(app, app->config.height / 12, app->config.height / 24, (app->config.width / 12) * 6, (app->config.height / 12) * 11, app->colors.green);
    else
        pageButtons[1] = nullBtn;

    SDL_RenderPresent(app->renderer);
}

int createBoxPage(App *app, SDL_Rect *buttons, int size, int page){
    int x, y, i = 10 * page;
    int xBox = 0, yBox = 0;

    for(x = 0; x < 5; x++){
        for(y = 0; y < 2; y++){
            if(i >= size)
                break;
            xBox = ((app->config.width / 3) * y) + 10*y + app->config.width/5;
            yBox = ((app->config.height / 8) * x) + 10*x + app->config.height/6;
            buttons[i] = createRect(app, app->config.height / 8, app->config.height / 8, xBox, yBox, app->colors.green);
            i++;
        }
        if(i >= size)
            break;
    }

    return i - 10 * page; // Return number of elements printed
}
