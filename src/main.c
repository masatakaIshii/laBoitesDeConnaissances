#include <stdlib.h>
#include <stdio.h>
#include "headers/common.h"
#include "headers/play.h"

int main(int argc, char **argv) {
    App app;

    // Start SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Unable to init SDL: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_WM_SetIcon(SDL_LoadBMP("img/icon.bmp"), NULL); // Chargement de l'icone du programme
    SDL_WM_SetCaption(".::. The box of knowledge .::.", NULL); // Chargement du nom du programme

    loadApp(&app);

    mainEventLoop(&app);

    SDL_Quit();

    return EXIT_SUCCESS;
}
