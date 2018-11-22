#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include "../headers/common.h"

void displayHomeScreen(SDL_Surface* screen, Config *config, Colors *colors){
    // On set la couleur du fond d'écran
    SDL_FillRect(screen, NULL, colors->blue);

    // On creer le boutton Play
    createRect(screen, config->width/3, config->height/1.5, config->width/12, config->height/4, colors->green);

    // On creer le boutton Create
    createRect(screen, config->width/3, config->height/1.5, (config->width/12)*7, config->height/4, colors->yellow);

    // On attend un evenement
    mainEventLoop(screen, config);
}

void mainEventLoop(SDL_Surface* screen, Config *config){
    SDL_Event event;
    int done = 0;

    while (!done){
        SDL_WaitEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT:
                done = 1;
                break;
            case SDL_VIDEORESIZE:
                config->height = event.resize.h;
                screen->w = config->height * 1,77;
                break;
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE){
                    done = 1;
                    break;
                }
        }

        // DRAW HERE

        // Update the screen
        SDL_Flip(screen);
    }
}

void createRect(SDL_Surface *screen, int width, int height, int x, int y, Uint32 color){
    SDL_Surface *rect = NULL;
    SDL_Rect position;

    rect = SDL_CreateRGBSurface(SDL_HWSURFACE, width, height, BPP, 0, 0, 0, 0);
    verifyPointer(rect, "Unable to load rectangle");

    setPosition(&position, x, y);

    SDL_FillRect(rect, NULL, color);
    SDL_BlitSurface(rect, NULL, screen, &position);

    SDL_FreeSurface(rect);
}

void verifyPointer(void *pointer, char *message){
    if(!pointer){
        printf("%s %s\n", message, SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

void setPosition(SDL_Rect *position, int x, int y){
    position->x = x;
    position->y = y;
}

void loadColors(SDL_Surface *screen, Colors *colors){
    colors->blue = SDL_MapRGB(screen->format, 93, 97, 203);
    colors->lightblue = SDL_MapRGBA(screen->format, 0, 0, 0, 0);
    colors->green = SDL_MapRGBA(screen->format, 86, 197, 138, 0);
    colors->yellow = SDL_MapRGBA(screen->format, 191, 187, 80, 0);
}

void loadConfig(Config *config){
    config->height = 480; // A configurer dans le fichier de config
    config->width = config->height * 1.77; // Largeur intialisé au format 16/9 suivant la hauteur
}
