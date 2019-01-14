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
    int idList = (int)strtol(app->model.query.selectQuery.listColumnsRows[(i+page) + page*9][0], NULL, 0);
    SDL_Rect *listButtons = NULL;
    SDL_Event event;
    int done = 0;

    printf("Id de la boite: %d\n", idList);
    // Getting data
    // getList(idList);
    // listbuttons = malloc()

    while (!done) {
        SDL_WaitEvent(&event);
        commonEvents(app, event, &done);
        switch (event.type) {
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
