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

int createCustumElementsPage(App *app, SDL_Rect *buttons, int sizeElements, int page, DisplayManager display) {
    int x, y;
    int xBox = 0;
    int yBox = 0;
    int currentIndex = display.nbElements * page;
    Position *pos = &(display.pos);

    for (y = 0; y < display.nbColumns; y++) {
        for (x = 0; x < display.nbRows; x++) {
            if (currentIndex >= sizeElements) {
                break;
            }

            xBox = (display.elementW + pos->stepX) * x + pos->startX;
            yBox = (display.elementH + pos->stepY) * y + pos->startY;
            buttons[currentIndex] = createRect(app, display.elementW, display.elementH, xBox, yBox, app->colors.green);
            currentIndex++;
        }

        if (currentIndex >= sizeElements) {
            break;
        }
    }

    return currentIndex - display.nbElements * display.currentPage;
}

void displayPageButtons(App *app, int page, SDL_Rect *pageButtons, int nbElements, int nbTotalOfBox) {
    SDL_Rect nullBtn = {0};

    if (page != 0) {
        pageButtons[0] = createRect(app, wRatio16(app, 0.7), hRatio9(app, 0.4), wRatio16(app, 8.5), hRatio9(app, 7.25), app->colors.green);
    } else {
        pageButtons[0] = nullBtn;
    }

    if (nbElements * (page + 1) < nbTotalOfBox) {
        pageButtons[1] = createRect(app, wRatio16(app, 0.7), hRatio9(app, 0.4), wRatio16(app, 10.5), hRatio9(app, 7.25), app->colors.green);
    } else {
        pageButtons[1] = nullBtn;
    }
}

void displayManageButtons(App *app, SDL_Rect *manageButtons, char boxManageText[2][11]) {

    manageButtons[0] = createRect(app, wRatio16(app, 3), hRatio9(app, 1.5), wRatio16(app, 1),  hRatio9(app, 2.5), app->colors.lightblue);

    manageButtons[1] = createRect(app, wRatio16(app, 3), hRatio9(app, 1.5), wRatio16(app, 1), hRatio9(app, 5.5), app->colors.red);

    renderTextManageButton(app, manageButtons, boxManageText);
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
