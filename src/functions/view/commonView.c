/*
** Filename : commonView.c
**
** Made by  : Masataka ISHII
**
** Description  : common view boxes functions
*/

#include "../../headers/view/commonView.h"

DisplayManager displayManagerConstructor(int elementHeight, int elementWidth,
                                         int nbColomns, int nbRows,
                                         int startX, int startY,
                                         int stepX, int stepY) {
    DisplayManager display;

    display.elementH = elementHeight;
    display.elementW = elementWidth;

    display.nbColumns = nbColomns;
    display.nbRows = nbRows;
    display.nbElements = nbRows * nbColomns;

    display.pos.startX = startX;
    display.pos.startY = startY;

    display.pos.stepX = stepX;
    display.pos.stepY = stepY;

    return display;
}






void renderTextManageButton(App *app, SDL_Rect *manageButtons, char boxManageText[2][11]) {
    typeRenderText typeText = TEXT_BLENDED;

    SDL_Texture *createText = textToTexture(app, app->config.fontCambriab, boxManageText[0], 100, typeText, app->colors.black);
    SDL_Texture *deleteText = textToTexture(app, app->config.fontCambriab, boxManageText[1], 100, typeText, app->colors.black);

    SDL_RenderCopy(app->renderer, createText, NULL, &manageButtons[0]);
    SDL_RenderCopy(app->renderer, deleteText, NULL, &manageButtons[1]);

    SDL_DestroyTexture(createText);
    SDL_DestroyTexture(deleteText);
}
