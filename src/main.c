#include <stdlib.h>
#include <stdio.h>
#include "headers/common.h"
#include "headers/play.h"

int main(int argc, char **argv) {
    App app;
    int returnStat;

    // Start SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Unable to init SDL: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    loadApp(&app);

    returnStat = mainEventLoop(&app);

    quitApp(&app);

    return returnStat;
}
