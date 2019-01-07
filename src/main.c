/*
** Filename : main.c
**
** Made by  : Baptiste LEGO
**
** Description  : main function start and quit App
*/

#include <stdlib.h>
#include <stdio.h>
#include "headers/common.h"
#include "headers/play/box.h"
#include "headers/model/modelSelect.h"
#include "headers/model/modelShow.h"
#include "headers/model/modelIUD.h"

int main(int argc, char **argv) {
    App app;
    int returnStat;

    freopen("CON", "w", stdout);
    freopen("CON", "r", stdin);
    freopen("CON", "w", stderr);

    // Start SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Unable to init SDL: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    /*if(TTF_Init() < 0) {
        fprintf(stderr, "Unable to init SDL_ttf: %s\n", TTF_GetError());
        return EXIT_FAILURE;
    }*/

    loadApp(&app);

    returnStat = mainEventLoop(&app);

    quitApp(&app);

    return returnStat;
}
