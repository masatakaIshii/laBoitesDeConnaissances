/*
** Filename : card.c
**
** Made by  : Baptiste LEGO
**
** Description  : card functions
*/

#include <time.h>
#include "../../headers/common.h"
#include "../../headers/play/card.h"
#include "../../headers/model/cardModel.h"

enum {WIN, FAIL};

void newCard(App *app, SelectQuery cards){
    SDL_Rect pageButton;
    SDL_Event event;
    int done = 0;
    int cardRow;

    // TAKE RANDOM CARD
    cardRow = randomCard(app, cards);
    if(cardRow < 0){
        printf("Error\n");
        exit(EXIT_FAILURE);
    }

    while (!done) {
        SDL_WaitEvent(&event);
        commonEvents(app, event, &done);
        switch (event.type) {
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT){
                    if(inRect(pageButton, event.button.x, event.button.y)){
                        cardResponse(app, cards.listColumnsRows[cardRow]);
                        done = 1;
                    }
                }
            break;
        }
        displayCard(app, cards.listColumnsRows[cardRow], &pageButton);
    }
}

void cardResponse(App *app, char **card){
    SDL_Rect pageButtons[2];
    SDL_Event event;
    int done = 0;

    while (!done) {
        SDL_WaitEvent(&event);
        commonEvents(app, event, &done);
        switch (event.type) {
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT){
                    if(inRect(pageButtons[WIN], event.button.x, event.button.y)){
                        setNewCardValidation(app, card[0]);
                        done = 1;
                    }
                    if(inRect(pageButtons[FAIL], event.button.x, event.button.y)){
                        printf("Dommage..\n");
                        done = 1;
                    }
                }
            break;
        }
        displayResponse(app, card, pageButtons);
    }
}

int randomCard(App *app, SelectQuery cards){
    int i, random, counter = 0;

    random = rand() % numberOfValidCards(app, cards);

    for(i = 0; i < cards.numberRows; i++){
        if(counter == random && isValidCard(cards.listColumnsRows[i]))
            return i;
        if(isValidCard(cards.listColumnsRows[i]))
            counter++;
    }

    return -1;
}

int numberOfValidCards(App *app, SelectQuery cards){
    int i, counter = 0;

    for(i = 0; i < cards.numberRows; i++){
        if(isValidCard(cards.listColumnsRows[i]))
            counter++;
    }

    return counter;
}

int isValidCard(char **card){
    time_t nowSeconds = time(NULL);
    int diffSeconds, diffHour, diffMin;

    diffSeconds = (int)nowSeconds - intConvertor(card[7]);
    diffMin = diffSeconds / 60;
    diffHour = diffSeconds / 3600;

    switch (intConvertor(card[6])){
        case 1:
            if(diffMin < 10)
                return 0;
        break;
        case 2:
            if(diffHour < 24)
                return 0;
        break;
        case 3:
            if(diffHour < 7*24)
                return 0;
        break;
        case 4:
            if(diffHour < 30*24)
                return 0;
        break;
        case 5:
            if(diffHour < 68*24)
                return 0;
        break;
    }

    return 1;
}


/*///////////////////////// DISPLAY \\\\\\\\\\\\\\\\\\\\\\\\\\*/


void displayCard(App *app, char **card, SDL_Rect *pageButton){
    SDL_Rect textPos;

    // Setting background
    SDL_SetRenderDrawColor(app->renderer, app->colors.blue[0], app->colors.blue[1], app->colors.blue[2], app->colors.blue[3]);
    SDL_RenderClear(app->renderer);

    // Texts
    writeTitle(app, card[1]);
    textPos = createRect(app, wRatio16(app, 10), hRatio9(app, 2), wRatio16(app, 3), hRatio9(app, 3), app->colors.blue);
    renderText(app, textPos, app->config.fontCambriab, card[3], 50, TEXT_BLENDED, app->colors.white);

    // Button
    *pageButton = createRect(app, wRatio16(app, 5), hRatio9(app, 1), wRatio16(app, 5.5), hRatio9(app, 7) + 40, app->colors.yellow);
    renderText(app, *pageButton, app->config.fontCambriab, "VOIR REPONSE", 70, TEXT_BLENDED, app->colors.white);

    // Refresh screen
    SDL_RenderPresent(app->renderer);
}

void displayResponse(App *app, char **card, SDL_Rect *pageButtons){
    SDL_Rect textPos;

    // Setting background
    SDL_SetRenderDrawColor(app->renderer, app->colors.blue[0], app->colors.blue[1], app->colors.blue[2], app->colors.blue[3]);
    SDL_RenderClear(app->renderer);

    // Texts
    writeTitle(app, card[1]);
    textPos = createRect(app, wRatio16(app, 10), hRatio9(app, 2), wRatio16(app, 3), hRatio9(app, 3), app->colors.blue);
    renderText(app, textPos, app->config.fontCambriab, card[4], 50, TEXT_BLENDED, app->colors.white);

    // Button
    pageButtons[WIN] = createRect(app, wRatio16(app, 3), hRatio9(app, 1), wRatio16(app, 4), hRatio9(app, 7) + 40, app->colors.green);
    renderText(app, pageButtons[WIN], app->config.fontCambriab, "J'AI BON !", 70, TEXT_BLENDED, app->colors.white);

    pageButtons[FAIL] = createRect(app, wRatio16(app, 3), hRatio9(app, 1), wRatio16(app, 9), hRatio9(app, 7) + 40, app->colors.red);
    renderText(app, pageButtons[FAIL], app->config.fontCambriab, "J'AI FAUX :(", 70, TEXT_BLENDED, app->colors.white);

    // Refresh screen
    SDL_RenderPresent(app->renderer);
}
