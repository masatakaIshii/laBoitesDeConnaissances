/*
** Filename : box.c
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

void playMode(App *app){
    SDL_Event event;
    SDL_Rect pageButtons[2];
    SDL_Rect boxButtons[130];
    int nbOfBox = 0;
    int done = 0;
    int page = 0;
    int i = 0;

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
                    // Changement de page
                    if(inRect(pageButtons[0] , event.button.x, event.button.y))
                        page--;
                    else if(inRect(pageButtons[1] , event.button.x, event.button.y))
                        page++;

                    // Affichage d'une boite
                    for(i = 0; i < nbOfBox; i++){
                        if(inRect(boxButtons[i], event.button.x, event.button.y))
                            listMenu(app, page, i);
                    }
                }
            break;
        }
        displayHomePlay(app, page, pageButtons, boxButtons, &nbOfBox);
    }
}

void displayHomePlay(App *app, int page, SDL_Rect *pageButtons, SDL_Rect *boxButtons, int *nbOfBox){
    // Récuperer le nombre de boites et le nombre de listes par boite dans la bdd (count sur les listes + nom de la boite)
    SDL_Rect nullBtn = {0};
    char box[130];

    // On set la couleur du fond d'ecran
    SDL_SetRenderDrawColor(app->renderer, app->colors.blue[0], app->colors.blue[1], app->colors.blue[2], app->colors.blue[3]);
    SDL_RenderClear(app->renderer);

    // Creation des boites
    *nbOfBox = createBoxPage(app, boxButtons, box, sizeof(box), page);

    // Conditions pour les boutons de pages
    if(page != 0)
        pageButtons[0] = createRect(app, app->config.height / 12, app->config.height / 24, (app->config.width / 12) * 5, (app->config.height / 12) * 11, app->colors.green);
    else
        pageButtons[0] = nullBtn;

    if(24 * (page+1) < sizeof(box))
        pageButtons[1] = createRect(app, app->config.height / 12, app->config.height / 24, (app->config.width / 12) * 6, (app->config.height / 12) * 11, app->colors.green);
    else
        pageButtons[1] = nullBtn;

    SDL_RenderPresent(app->renderer);
}

int createBoxPage(App *app, SDL_Rect *buttons, char *box, int size, int page){
    int x, y, i = 24 * page;
    int xBox = 0, yBox = 0;

    for(x = 0; x < 4; x++){
        for(y = 0; y < 6; y++){
            xBox = ((app->config.height / 6) * y) + 10*y + app->config.width/5;
            yBox = ((app->config.height / 6) * x) + 10*x + app->config.height/6;
            buttons[i] = createRect(app, app->config.height / 6, app->config.height / 6, xBox, yBox, app->colors.green);
            i++;
            if(i >= size)
                break;
        }
        if(i >= size)
            break;
    }

    return i - 24 * page; // Retourne le nombre d'elements sur la page
}
