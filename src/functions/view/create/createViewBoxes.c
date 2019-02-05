/*
** Filename : createViewBoxes.c
**
** Made by  : Baptiste LEGO, Masataka ISHII
**
** Description  : view boxes functions
*/

#include "../../../headers/view/create/createViewBoxes.h"

void displayElements(App *app, SelectQuery *elements, CreateInfo *cInfo, CreateButtons *cButtons, CreatePage *cPages) {

    int elementHeight = hRatio9(app, 1.25),     elementWidth = wRatio16(app, 1.25);
    int nbColomns = 3,                          nbRows = 2;
    int startX = wRatio16(app, 5.5),            startY = hRatio9(app, 2);
    int stepX = wRatio16(app, 3.5),             stepY = hRatio9(app, 0.25);

    DisplayManager display = displayManagerConstructor(elementHeight, elementWidth, nbColomns, nbRows, startX, startY, stepX, stepY);

    strcpy(cButtons->buttonText0, "CREATE BOX");
    strcpy(cButtons->buttonText1, "DELETE BOX");

    SDL_SetRenderDrawColor(app->renderer, app->colors.blue[0], app->colors.blue[1], app->colors.blue[2], app->colors.blue[3]);
    SDL_RenderClear(app->renderer);

    // Creating boxes
    cPages->nbElementsPage = createCustumElementsPage(app, cButtons, cPages, display);
//
//    displayPageButtons(app, page, pageButtons, display.nbElements, nbTotalOfBox);
//
//    displayManageButtons(app, manageButtons, boxManageText);
//
//    SDL_RenderPresent(app->renderer);
}

int createCustumElementsPage(App *app, CreateButtons *cButtons, CreatePage *cPages, DisplayManager display) {
    int x, y;
    int xBox = 0;
    int yBox = 0;
    int i = display.nbElements * cPages->page;
    Position *pos = &(display.pos);

    for (y = 0; y < display.nbColumns; y++) {
        for (x = 0; x < display.nbRows; x++) {
            if (i >= cPages->nbTotalElements) {
                break;
            }
            //TODO : rendertext of name of element and date
            xBox = (display.elementW + pos->stepX) * x + pos->startX;
            yBox = (display.elementH + pos->stepY) * y + pos->startY;
            fillSizePosColor(app, &cPages->elementButtons[i], display.elementW, display.elementH, xBox, yBox, app->colors.green);
            i++;
        }

        if (i >= cPages->nbTotalElements) {
            break;
        }
    }

    return i - display.nbElements * display.currentPage;
}

void fillSizePosColor(App *app, SDL_Rect *rectToFill, int width, int height, int x, int y, Uint8 *color){
    rectToFill->w = width;
    rectToFill->w = height;
    rectToFill->x = x;
    rectToFill->y = y;

    SDL_SetRenderDrawColor(app->renderer, color[0], color[1], color[2], color[3]);

    SDL_RenderFillRect(app->renderer, rectToFill);
}

void displayCard (App *app, CreateInfo *cInfo,CreateButtons *cButtons){
    SDL_SetRenderDrawColor(app->renderer, 200, 200, 200, 200);
    SDL_RenderClear(app->renderer);

    SDL_RenderPresent(app->renderer);
}
