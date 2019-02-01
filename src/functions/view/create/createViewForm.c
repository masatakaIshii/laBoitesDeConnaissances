/*
** Filename : createViewFrom.c
**
** Made by  : Masataka ISHII
**
** Description  : view form functions
*/
#include "../../../headers/view/create/createViewForm.h"
void displayAllInputs(App *app, InputManager *input, int numberFields){

    //DisplayManager display = displayManagerConstructor(elementHeight, elementWidth, nbColomns, nbRows, startX, startY, stepX, stepY);

    SDL_SetRenderDrawColor(app->renderer, app->colors.blue[0], app->colors.blue[1], app->colors.blue[2], app->colors.blue[3]);
    SDL_RenderClear(app->renderer);

}
