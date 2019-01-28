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
#include "../../headers/model/listModel.h"

void listMenu(App *app, SelectQuery boxes, int page, int i){
    SDL_Rect *listButtons = NULL;
    SDL_Event event;
    int done = 0;

    // Getting data
    SelectQuery lists = getLists(app, boxes.listColumnsRows[(i+page) + page*9][0]);
    listButtons = malloc(lists.numberRows * sizeof(SDL_Rect));

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
        displayHomeBox(app, lists, listButtons);
    }

    free(listButtons);
}


/*///////////////////////// DISPLAY \\\\\\\\\\\\\\\\\\\\\\\\\\*/


void displayHomeBox(App *app, SelectQuery lists, SDL_Rect *listButtons){
    // On set la couleur du fond d'ecran
    SDL_SetRenderDrawColor(app->renderer, app->colors.blue[0], app->colors.blue[1], app->colors.blue[2], app->colors.blue[3]);
    SDL_RenderClear(app->renderer);

    // Creation des boites
    createListPage(app, lists, listButtons, lists.numberRows);

    SDL_RenderPresent(app->renderer);
}

int createListPage(App *app, SelectQuery lists, SDL_Rect *buttons, int size){
    int x, y, i = 0;
    int xBox = 0, yBox = 0;
    SDL_Rect textPos;

    for(x = 0; x < 5; x++){
        for(y = 0; y < 2; y++){
            if(i >= size)
                break;
            xBox = ((app->config.width / 3) * y) + 10*y + app->config.width/5;
            yBox = ((app->config.height / 8) * x) + 10*x + app->config.height/6;
            buttons[i] = createRect(app, app->config.height / 8, app->config.height / 8, xBox, yBox, app->colors.yellow);

            // Create text
            textPos = buttons[i];
            textPos.x += app->config.height / 8 + 5;
            textPos.w *= 4;
            renderText(app, textPos, app->config.fontCambriab, lists.listColumnsRows[i][1], 30, TEXT_BLENDED, app->colors.white);
            i++;
        }
        if(i >= size)
            break;
    }

    return i; // Retourne le nombre d'elements sur la page
}
