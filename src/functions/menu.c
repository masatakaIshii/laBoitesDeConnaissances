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
#include "../headers/menu.h"
#include "../headers/stats.h"
#include "../headers/play/box.h"
#include "../headers/controll/create.h"

enum {PLAY, CREATE, STATS};

int mainEventLoop(App *app) {
    SDL_Rect buttons[3];
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
            break;

            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT){
                    if(inRect(buttons[PLAY] , event.button.x, event.button.y))
                        playMode(app);
                    else if(inRect(buttons[CREATE] , event.button.x, event.button.y))
                        createMode(app);
                    else if(inRect(buttons[STATS], event.button.x, event.button.y))
                        stats(app);
                }
            break;
        }
        displayMenu(app, buttons);
    }

    return (done) ? EXIT_SUCCESS : EXIT_FAILURE;
}


/* //////////////////////// DISPLAY \\\\\\\\\\\\\\\\\\\\\\\\\ */


void displayMenu(App *app, SDL_Rect *buttons) {
    // Background color
    SDL_SetRenderDrawColor(app->renderer, app->colors.blue[0], app->colors.blue[1], app->colors.blue[2], app->colors.blue[3]);
    SDL_RenderClear(app->renderer);

    // Create the buttons
    buttons[PLAY] = createRect(app, app->config.width / 3, app->config.height / 1.5, app->config.width / 12, app->config.height / 4, app->colors.green);
    buttons[CREATE] = createRect(app, app->config.width / 3, app->config.height / 1.5, (app->config.width / 12) * 7, app->config.height / 4, app->colors.yellow);
    buttons[STATS] = createRect(app, wRatio16(app, 2), hRatio9(app, 1), wRatio16(app, 1), app->config.height / 18, app->colors.yellow);
    renderText(app, buttons[STATS], app->config.fontCambriab, "STATS", 50, TEXT_BLENDED, app->colors.black);

    RenderMainTexts(app);

    // Refresh screen
    SDL_RenderPresent(app->renderer);
}

void RenderMainTexts (App *app) {
    //Define the placement of texts
    SDL_Rect playTextRect = {wRatio16(app, 1.65), hRatio9(app, 4), wRatio16(app, 4.5), hRatio9(app, 2.25)};
    SDL_Rect createTextRect = {wRatio16(app, 9.65), hRatio9(app, 4), wRatio16(app, 4.5), hRatio9(app, 2.25)};
    SDL_Rect titleTextRect = {app->config.width / 3.75, 0, app->config.width / 2.25, app->config.height / 5};

    // Render the texts
    renderText(app, playTextRect, app->config.fontCambriab, "PLAY MODE", 50, TEXT_BLENDED, app->colors.black);
    renderText(app, createTextRect, app->config.fontCambriab, "CREATE MODE", 50, TEXT_BLENDED, app->colors.black);
    renderText(app, titleTextRect, app->config.fontCambriab, "THE BOX OF KNOWLEDGE", 55, TEXT_BLENDED, app->colors.white);
}
