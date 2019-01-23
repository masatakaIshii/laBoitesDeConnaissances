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

    for (x = 0; x < display.nbColumns; x++) {
        for (y = 0; y < display.nbRows; y++) {
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
