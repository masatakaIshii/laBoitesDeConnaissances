#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "../headers/common.h"
#include "../headers/play.h"

void playMode(App *app){
    SDL_Event event;
    int done = 0;

    while (!done) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                done = 1; // On quitte la boucle et on retourne au menu principal
                break;
            case SDL_WINDOWEVENT:
                if(event.window.event == SDL_WINDOWEVENT_RESIZED)
                    resizeScreen(app, event.window.data2);
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    done = 1; // On quitte la boucle et on retourne au menu principal
                    break;
                }
        }
        displayHomePlay(app);
    }
}

void displayHomePlay(App *app){
    // On set la couleur du fond d'ecran
    SDL_SetRenderDrawColor(app->renderer, app->colors.blue[0], app->colors.blue[1], app->colors.blue[2], app->colors.blue[3]);
    SDL_RenderClear(app->renderer);

    SDL_RenderPresent(app->renderer);
}
