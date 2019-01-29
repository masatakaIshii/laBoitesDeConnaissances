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

enum {RESET, PLAY};

void game(App *app, char **list, int idList){
    SDL_Rect pageButtons[2];
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
        displayGame(app, list, cards, pageButtons);
    }
}


/*///////////////////////// DISPLAY \\\\\\\\\\\\\\\\\\\\\\\\\\*/


void displayGame(App *app, char **list, SelectQuery cards, SDL_Rect *pageButtons){
    SDL_Rect textPos;

    // Setting background
    SDL_SetRenderDrawColor(app->renderer, app->colors.blue[0], app->colors.blue[1], app->colors.blue[2], app->colors.blue[3]);
    SDL_RenderClear(app->renderer);

    // Write title
    writeTitle(app, list[1]);

    // Create buttons
    pageButtons[RESET] = createRect(app, wRatio16(app, 2), hRatio9(app, 1), wRatio16(app, 1), hRatio9(app, 1) - 20, app->colors.lightblue);
    renderText(app, pageButtons[RESET], app->config.fontCambriab, "RESET", 50, TEXT_BLENDED, app->colors.black);

    pageButtons[PLAY] = createRect(app, wRatio16(app, 4), hRatio9(app, 1), wRatio16(app, 6), hRatio9(app, 7) + 40, app->colors.green);
    renderText(app, pageButtons[PLAY], app->config.fontCambriab, "JOUER", 80, TEXT_BLENDED, app->colors.white);

    // Create cards
    textPos = createRect(app, wRatio16(app, 4), hRatio9(app, 5), wRatio16(app, 3), hRatio9(app, 2), hexToRgb(list[5]));
    renderText(app, textPos, app->config.fontTimes, "13", 150, TEXT_BLENDED, app->colors.white);

    textPos = createRect(app, wRatio16(app, 4), hRatio9(app, 5), wRatio16(app, 9), hRatio9(app, 2), app->colors.red);
    renderText(app, textPos, app->config.fontTimes, "8", 150, TEXT_BLENDED, app->colors.white);

    // Refresh screen
    SDL_RenderPresent(app->renderer);
}
