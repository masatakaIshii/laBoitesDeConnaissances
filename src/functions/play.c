#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include "../headers/common.h"
#include "../headers/play.h"

void playMode(App *app){
    SDL_Event event;
    int done = 0;

    while (!done) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                done = 1; // On quitte la boucle ie le programme
                break;
            case SDL_VIDEORESIZE:
                resizeScreen(app, event.resize.h);
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    done = 1; // On quitte la boucle ie le programme
                    break;
                }
        }
        displayHomePlay(app);
    }
}

void displayHomePlay(App *app){
    // On set la couleur du fond d'ecran
    SDL_FillRect(app->screen, NULL, app->colors.blue);

    SDL_Flip(app->screen);
}
