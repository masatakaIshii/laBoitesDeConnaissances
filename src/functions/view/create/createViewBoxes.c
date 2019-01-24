/*
** Filename : createViewBoxes.c
**
** Made by  : Baptiste LEGO, Masataka ISHII
**
** Description  : view boxes functions
*/

#include "../../../headers/view/create/createViewBoxes.h"

void displayBoxes(App *app, int page, SDL_Rect *pageButtons, SDL_Rect *boxButtons, SDL_Rect *manageButtons, int *nbOfBox, int nbTotalOfBox) {

    int elementHeight = hRatio9(app, 1.25),     elementWidth = wRatio16(app, 1.25);
    int nbColomns = 2,                          nbRows = 4;
    int startX = wRatio16(app, 5.5),            startY = hRatio9(app, 2);
    int stepX = wRatio16(app, 3.5),             stepY = hRatio9(app, 0.25);

    char boxManageText[2][11];

    strcpy(boxManageText[0], "CREATE BOX");
    strcpy(boxManageText[1], "DELETE BOX");

    DisplayManager display = displayManagerConstructor(elementHeight, elementWidth, nbColomns, nbRows, startX, startY, stepX, stepY);

    SDL_SetRenderDrawColor(app->renderer, app->colors.blue[0], app->colors.blue[1], app->colors.blue[2], app->colors.blue[3]);
    SDL_RenderClear(app->renderer);

    // Creating boxes
    *nbOfBox = createCustumElementsPage(app, boxButtons, nbTotalOfBox, page, display);

    displayPageButtons(app, page, pageButtons, display.nbElements, nbTotalOfBox);

    displayManageButtons(app, manageButtons, boxManageText);

    SDL_RenderPresent(app->renderer);
}
