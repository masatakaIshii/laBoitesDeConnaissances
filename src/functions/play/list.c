/*
** Filename : list.c
**
** Made by  : Baptiste LEGO
**
** Description  : play mode main functions
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "../../headers/common.h"
#include "../../headers/play/box.h"
#include "../../headers/play/list.h"

void listMenu(App *app, int page, int i){
    SDL_Rect listButtons[24];

    printf("Affichage de la boite %d\n", (i+page) + page*23);
    SDL_Event event;
    int done = 0;

    while (!done) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            // On quitte le programme
            case SDL_QUIT:
                quitApp(app);
                exit(EXIT_SUCCESS);
            break;

            case SDL_WINDOWEVENT:
                if(event.window.event == SDL_WINDOWEVENT_RESIZED)
                    resizeScreen(app, event.window.data2);
            break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    done = 1; // On quitte la boucle et on retourne au menu principal
                }
            break;

            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT){
                    // Affichage d'une liste
                }
            break;
        }
        displayHomeBox(app, listButtons);
    }
}

void displayHomeBox(App *app, SDL_Rect *listButtons){
    char list[24];

    // On set la couleur du fond d'ecran
    SDL_SetRenderDrawColor(app->renderer, app->colors.blue[0], app->colors.blue[1], app->colors.blue[2], app->colors.blue[3]);
    SDL_RenderClear(app->renderer);

    // Creation des boites
    createListPage(app, listButtons, list, sizeof(list));

    SDL_RenderPresent(app->renderer);
}

int createListPage(App *app, SDL_Rect *buttons, char *list, int size){
    int x, y, i = 0;
    int xBox = 0, yBox = 0;

    for(x = 0; x < 4; x++){
        for(y = 0; y < 6; y++){
            xBox = ((app->config.height / 6) * y) + 10*y + app->config.width/5;
            yBox = ((app->config.height / 6) * x) + 10*x + app->config.height/6;
            buttons[i] = createRect(app, app->config.height / 6, app->config.height / 6, xBox, yBox, app->colors.yellow);
            i++;
            if(i >= size)
                break;
        }
        if(i >= size)
            break;
    }

    return i; // Retourne le nombre d'elements sur la page
}
