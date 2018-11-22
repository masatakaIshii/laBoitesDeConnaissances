#include <stdlib.h>
#include <stdio.h>
#include "headers/common.h"

int main(int argc, char** argv){
    SDL_Surface *screen = NULL;

    // On charge la config
    Config config;
    loadConfig(&config, 480);

    // Start SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Unable to init SDL: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_WM_SetIcon(SDL_LoadBMP("img/icon.bmp"), NULL); // Chargement de l'icone du programme
    SDL_WM_SetCaption(".::. The box of knowledge .::.", NULL); // Chargement du nom du programme

    // Create the window
    screen = SDL_SetVideoMode(config.width, config.height, BPP, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
    verifyPointer(screen, "Unable to set video mode");

    mainEventLoop(screen, &config);

    SDL_Quit();

    return EXIT_SUCCESS;
}
