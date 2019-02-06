/*
** Filename : createDelete.c
**
** Made by  : Masataka ISHII
**
** Description  : delete elements functions
*/

#include "../../../headers/controll/create/createDelete.h"

void deleteElement(App *app, char *tableName, char **info){
    SDL_Event event;
    SDL_Rect deleteButton;
    int done = 0;
    int checkDel = 0;

    while (!done){
        SDL_WaitEvent(&event);
        commonEvents(app, event, &done);

        switch (event.type){
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT){

                }
        }

    }

}
