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
#include "../headers/controll/create/create.h"
#include "../headers/model/modelHelper/modelSelect.h"

int mainEventLoop(App *app) {
    SDL_Rect buttons[2];
    SDL_Event event;
    int done = 0;

    // TEST tous les cas
    SelectQuery boxes = getSelectQuery(app, "SELECT * FROM box");
    SelectQuery list = getSelectQuery(app, "SELECT * FROM list");
    SelectQuery card = getSelectQuery(app, "SELECT * FROM card");
    // TEST tous les cas

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
                    createMode(app, "box", NULL);
                    //createMode(app, "list", boxes.listColumnsRows[0]);
                    //createMode(app, "card", list.listColumnsRows[0]);
                    //createMode(app, "end", card.listColumnsRows[2]);
                    // Fonction CREATE
            break;

            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT){
                    // MODE PLAY
                    if(inRect(buttons[0] , event.button.x, event.button.y))
                        playMode(app);
                    // MODE CREATE
                    else if(inRect(buttons[1] , event.button.x, event.button.y)){
                        // Fonction CREATE
                        createMode(app, "box", NULL);
                        //createMode(app, "list", boxes.listColumnsRows[0]);
                        //createMode(app, "card", list.listColumnsRows[0]);
                        //createMode(app, "end", card.listColumnsRows[0]);
                    }
                }
            break;
        }
        displayMenu(app, buttons);
    }

    //fin test
    quitSelectQuery(&boxes);
    quitSelectQuery(&list);
    quitSelectQuery(&card);
    // fin test

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
    SDL_Color black = { 0, 0, 0};
    SDL_Color white = { 255, 255, 255 };

    //Define the placement of texts
    SDL_Rect playTextRect = {wRatio16(app, 1.65), hRatio9(app, 4), wRatio16(app, 4.5), hRatio9(app, 2.25)};
    SDL_Rect createTextRect = {wRatio16(app, 9.65), hRatio9(app, 4), wRatio16(app, 4.5), hRatio9(app, 2.25)};
    SDL_Rect titleTextRect = {app->config.width / 3.75, 0, app->config.width / 2.25, app->config.height / 5};

    // Render the texts
    renderText(app, playTextRect, app->config.fontCambriab, "PLAY MODE", 55, TEXT_BLENDED, black);
    renderText(app, createTextRect, app->config.fontCambriab, "CREATE MODE", 55, TEXT_BLENDED, black);
    renderText(app, titleTextRect, app->config.fontCambriab, "THE BOX OF KNOWLEDGE", 75, TEXT_BLENDED, white);
}
