/*
** Filename : menu.c
**
** Made by  : Baptiste LEGO
**
** Description  : menu functions for events and display
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <mysql.h>
#include "../headers/common.h"
#include "../headers/play/box.h"
#include "../headers/controll/create.h"

int mainEventLoop(App *app) {
    SDL_Rect buttons[2];
    SDL_Event event;
    int done = 0;

    while (!done) {
        SDL_WaitEvent(&event);
        commonEvents(app, event, &done);
        switch (event.type){
            case SDL_KEYDOWN:
                // MODE PLAY
                if (event.key.keysym.scancode == SDL_SCANCODE_1)
                    playMode(app);
                // MODE CREATE
                if (event.key.keysym.scancode == SDL_SCANCODE_2)
                    createMode(app);
                    // Fonction CREATE
            break;

            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT){
                    // MODE PLAY
                    if(inRect(buttons[0] , event.button.x, event.button.y))
                        playMode(app);
                    // MODE CREATE
                    else if(inRect(buttons[1] , event.button.x, event.button.y))
                        // Fonction CREATE
                        createMode(app);
                }
            break;
        }
        displayMenu(app, buttons);
    }

    return (done) ? EXIT_SUCCESS : EXIT_FAILURE;
}


/* //////////////////////// DISPLAY \\\\\\\\\\\\\\\\\\\\\\\\\ */


void displayMenu(App *app, SDL_Rect *buttons) {

    // On set la couleur du fond d'ecran
    SDL_SetRenderDrawColor(app->renderer, app->colors.blue[0], app->colors.blue[1], app->colors.blue[2], app->colors.blue[3]);
    SDL_RenderClear(app->renderer);

    // On creer le boutton Play
    buttons[0] = createRect(app, app->config.width / 3, app->config.height / 1.5, app->config.width / 12, app->config.height / 4, app->colors.green);
    // On creer le boutton Create
    buttons[1] = createRect(app, app->config.width / 3, app->config.height / 1.5, (app->config.width / 12) * 7, app->config.height / 4, app->colors.yellow);

    RenderMainTexts(app);
    // Actualisation de l'ecran
    SDL_RenderPresent(app->renderer);

}

void RenderMainTexts (App *app) {
    typeRenderText typeText = TEXT_BLENDED;
    SDL_Color black = { 0, 0, 0};
    SDL_Color white = { 255, 255, 255 };

    //Create textures of all texts
    SDL_Texture *playText = textToTexture(app, app->config.fontCambriab, "PLAY MODE", 50, typeText, black);
    SDL_Texture *createText = textToTexture(app, app->config.fontCambriab, "CREATE MODE", 50, typeText, black);
    SDL_Texture *titleText = textToTexture(app, app->config.fontCambriab, "THE BOX OF KNOWLEDGE", 55, typeText, white);

    //Define the placement of texts
    SDL_Rect playTextRect = {wRatio16(app, 1.65), hRatio9(app, 4), wRatio16(app, 4.5), hRatio9(app, 2.25)};
    SDL_Rect createTextRect = {wRatio16(app, 9.65), hRatio9(app, 4), wRatio16(app, 4.5), hRatio9(app, 2.25)};
    SDL_Rect titleTextRect = {app->config.width / 3.75, 0, app->config.width / 2.25, app->config.height / 5};

    //Render texts
    SDL_RenderCopy(app->renderer, playText, NULL, &playTextRect);
    SDL_RenderCopy(app->renderer, createText, NULL, &createTextRect);
    SDL_RenderCopy(app->renderer, titleText, NULL, &titleTextRect);

    //Destroy after copy
    SDL_DestroyTexture(playText);
    SDL_DestroyTexture(createText);
    SDL_DestroyTexture(titleText);
}
