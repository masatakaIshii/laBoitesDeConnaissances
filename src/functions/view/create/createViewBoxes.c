/*
** Filename : createViewBoxes.c
**
** Made by  : Baptiste LEGO, Masataka ISHII
**
** Description  : view boxes functions
*/

#include "../../../headers/view/create/createViewBoxes.h"

void displayBoxes(App *app, int page, SDL_Rect *pageButtons, SDL_Rect *boxButtons, int *nbOfBox, int nbTotalOfBox) {
    SDL_Rect nullBtn = {0};
    int elementHeight = hRatio9(app, 1.25),            elementWidth = wRatio16(app, 1.25);
    int nbColomns = 2,                              nbRows = 3;
    int startX = wRatio16(app, 5.5),                startY = hRatio9(app, 2);
    int stepX = wRatio16(app, 3.5),                   stepY = hRatio9(app, 0.25);

    DisplayManager display = displayManagerConstructor(elementHeight, elementWidth, nbColomns, nbRows, startX, startY, stepX, stepY);

    SDL_SetRenderDrawColor(app->renderer, app->colors.blue[0], app->colors.blue[1], app->colors.blue[2], app->colors.blue[3]);
    SDL_RenderClear(app->renderer);

    // Creating boxes
    *nbOfBox = createCustumElementsPage(app, boxButtons, nbTotalOfBox, page, display);

    if (page != 0) {
        pageButtons[0] = createRect(app, wRatio16(app, 1.5), hRatio9(app, 1), wRatio16(app, 8.5), hRatio9(app, 7.25), app->colors.yellow);
    } else {
        pageButtons[0] = nullBtn;
    }

    if (display.nbElements * (page + 1) < nbTotalOfBox) {
        pageButtons[1] = createRect(app, wRatio16(app, 1.5), hRatio9(app, 1), wRatio16(app, 10.5), hRatio9(app, 7.25), app->colors.yellow);
    } else {
        pageButtons[1] = nullBtn;
    }

    SDL_RenderPresent(app->renderer);
}
