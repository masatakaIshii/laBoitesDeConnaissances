/*
** Filename : game.c
**
** Made by  : Baptiste LEGO
**
** Description  : game functions
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "../../headers/common.h"
#include "../../headers/play/game.h"
#include "../../headers/model/cardModel.h"

void game(App *app, char **list, int idList){
    SDL_Event event;
    int done = 0;
    SelectQuery cards;

    // Getting data
    cards = getCardsFromList(app, idList);

    while (!done) {
        SDL_WaitEvent(&event);
        commonEvents(app, event, &done);
        switch (event.type) {
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT){
                    // Action
                }
            break;
        }
        displayGame(app, list, cards);
    }
}


/*///////////////////////// DISPLAY \\\\\\\\\\\\\\\\\\\\\\\\\\*/


void displayGame(App *app, char **list, SelectQuery cards){
    SDL_Rect textPos;

    // Setting background
    SDL_SetRenderDrawColor(app->renderer, app->colors.blue[0], app->colors.blue[1], app->colors.blue[2], app->colors.blue[3]);
    SDL_RenderClear(app->renderer);

    // Write title
    writeTitle(app, list[1]);

    SDL_RenderPresent(app->renderer);
}
