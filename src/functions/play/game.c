/*
** Filename : game.c
**
** Made by  : Baptiste LEGO
**
** Description  : game functions
*/

#include "../../headers/common.h"
#include "../../headers/play/game.h"
#include "../../headers/play/card.h"
#include "../../headers/model/cardModel.h"
#include "../../headers/model/listModel.h"

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
                    if(inRect(pageButtons[PLAY], event.button.x, event.button.y) && numberOfValidCards(app, cards) > 0){
                        newCard(app, cards, list[L_COLOR]);
                        cards = getCardsFromList(app, idList); // Getting new data
                    }
                    else if(inRect(pageButtons[RESET], event.button.x, event.button.y)){
                        resetCards(app, idList);
                        cards = getCardsFromList(app, idList); // Getting new data
                    }
                }
            break;
        }
        displayGame(app, list, cards, pageButtons);
    }
}


/*///////////////////////// DISPLAY \\\\\\\\\\\\\\\\\\\\\\\\\\*/


void displayGame(App *app, char **list, SelectQuery cards, SDL_Rect *pageButtons){
    char str[5];
    SDL_Rect textPos;

    // Setting background
    SDL_SetRenderDrawColor(app->renderer, app->colors.blue[0], app->colors.blue[1], app->colors.blue[2], app->colors.blue[3]);
    SDL_RenderClear(app->renderer);

    // Write title
    writeTitle(app, list[NAME]);
    writeReturnKey(app);

    // Create buttons
    pageButtons[RESET] = createRect(app, wRatio16(app, 2), hRatio9(app, 1), wRatio16(app, 1), hRatio9(app, 1) - 20, app->colors.yellow);
    renderText(app, pageButtons[RESET], app->config.fontCambriab, "RESET", 50, TEXT_BLENDED, app->colors.white);

    pageButtons[PLAY] = createRect(app, wRatio16(app, 5), hRatio9(app, 1), wRatio16(app, 5.5), hRatio9(app, 7) + 40, app->colors.green);
    if(numberOfValidCards(app, cards) > 0)
        renderText(app, pageButtons[PLAY], app->config.fontCambriab, "TIRER UNE CARTE", 80, TEXT_BLENDED, app->colors.white);
    else
        renderText(app, pageButtons[PLAY], app->config.fontCambriab, "AUCUNE CARTE JOUABLE", 80, TEXT_BLENDED, app->colors.white);

    // Create cards
    sprintf(str, "%d", numberOfValidCards(app, cards));
    textPos = createRect(app, wRatio16(app, 4), hRatio9(app, 5), wRatio16(app, 3), hRatio9(app, 2), hexToRgb(list[L_COLOR]));
    renderText(app, textPos, app->config.fontTimes, str, 150, TEXT_BLENDED, app->colors.white);

    sprintf(str, "%d", cards.numberRows - numberOfValidCards(app, cards));
    textPos = createRect(app, wRatio16(app, 4), hRatio9(app, 5), wRatio16(app, 9), hRatio9(app, 2), app->colors.red);
    renderText(app, textPos, app->config.fontTimes, str, 150, TEXT_BLENDED, app->colors.white);

    // Refresh screen
    SDL_RenderPresent(app->renderer);
}
