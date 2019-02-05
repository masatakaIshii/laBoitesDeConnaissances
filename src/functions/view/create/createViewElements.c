/*
** Filename : createViewElements.c
**
** Made by  : Masataka ISHII
**
** Description  : view elements functions
*/

#include "../../../headers/view/create/createViewElements.h"

void displayElements(App *app, SelectQuery *elements, CreateInfo *cInfo, CreateButtons *cButtons, CreatePage *cPages) {

    int elementHeight = hRatio9(app, 1.25),     elementWidth = wRatio16(app, 1.25);
    int nbColomns = 3,                          nbRows = 2;
    int startX = wRatio16(app, 5.5),            startY = hRatio9(app, 2.75);
    int stepX = wRatio16(app, 3.5),             stepY = hRatio9(app, 0.25);

    DisplayManager display = displayManagerConstructor(elementHeight, elementWidth, nbColomns, nbRows, startX, startY, stepX, stepY);

    strcpy(cButtons->buttonText0, "CREATE BOX");
    strcpy(cButtons->buttonText1, "DELETE BOX");

    SDL_SetRenderDrawColor(app->renderer, cPages->mainPColor[0], cPages->mainPColor[1], cPages->mainPColor[2], cPages->mainPColor[3]);
    SDL_RenderClear(app->renderer);

    // Creating elements
    cPages->nbElementsPage = createCustumElementsPage(app, elements, cButtons, cPages, display);

    //displayPageButtons(app, cPages, display.nbElements);
//
//    displayManageButtons(app, manageButtons, boxManageText);
//
    SDL_RenderPresent(app->renderer);
}

int createCustumElementsPage(App *app, SelectQuery *elements, CreateButtons *cButtons, CreatePage *cPages, DisplayManager display) {
    int x, y;
    int i = display.nbElements * cPages->page;
    Position *pos = &(display.pos);
    TextRender tIndex;

    for (y = 0; y < display.nbColumns; y++) {
        for (x = 0; x < display.nbRows; x++) {
            if (i >= cPages->nbTotalElements) {
                break;
            }

            displayElementsInfos(app, elements, cPages, pos, display, i, &tIndex, y, x);
            i++;
        }

        if (i >= cPages->nbTotalElements) {
            break;
        }
    }

    return i - display.nbElements * cPages->page;
}

// Function to display elements in page with name and date infos
void displayElementsInfos(App *app, SelectQuery *elements, CreatePage *cPages, Position *pos, DisplayManager display, int i, TextRender *tRender, int y, int x){
    int xBox = (display.elementW + pos->stepX) * x + pos->startX;   // x position of rect of element
    int yBox = (display.elementH + pos->stepY) * y + pos->startY;   // y position of rect of element

    cPages->elementButtons[i] = createRect(app, display.elementW, display.elementH, xBox, yBox, cPages->pageBColor);

    // get text and position and w, h of index i
    sprintf(tRender->text, "%d", i + 1);
    tRender->length = strlen(tRender->text);
    tRender->rect.w = display.elementW / 3 * tRender->length;
    tRender->rect.h = display.elementH / 1.5;
    tRender->rect.x = getAppropriateXOrY(tRender->rect.w, display.elementW, xBox);
    tRender->rect.y = getAppropriateXOrY(tRender->rect.h, display.elementH, yBox);
    renderText(app, tRender->rect, app->config.fontCambriab, tRender->text, 70, TEXT_BLENDED, app->colors.black);

    // position and put color of name of element and render
    tRender->length = strlen(elements->listColumnsRows[i][1]);
    cPages->elementName[i] = createRect(app, (display.elementW / 10) * tRender->length, display.elementH / 2 , xBox + display.elementW * 1.125, yBox, cPages->mainPColor);
    renderText(app, cPages->elementName[i], app->config.fontCambriab, elements->listColumnsRows[i][1], 50, TEXT_BLENDED, app->colors.black);

    // position and put color of date of element and render
    tRender->length = strlen(elements->listColumnsRows[i][cPages->indexDate]);
    cPages->elementName[i] = createRect(app, (display.elementW / 10) * tRender->length, display.elementH / 2 , xBox + display.elementW * 1.125, yBox + display.elementH / 2, cPages->mainPColor);
    renderText(app, cPages->elementName[i], app->config.fontCambriab, elements->listColumnsRows[i][cPages->indexDate], 50, TEXT_BLENDED, app->colors.black);
}

int getAppropriateXOrY(int lengthChild, int lengthParent, int posParent){
    int diff = (lengthParent - lengthChild) / 2;

    return posParent + diff;
}
//void fillSizePosColor(App *app, SDL_Rect *rectToFill, int width, int height, int x, int y, Uint8 *color){
//    rectToFill->w = width;
//    rectToFill->w = height;
//    rectToFill->x = x;
//    rectToFill->y = y;
//
//    SDL_SetRenderDrawColor(app->renderer, color[0], color[1], color[2], color[3]);
//
//    SDL_RenderFillRect(app->renderer, rectToFill);
//}

void displayPageButtons(App *app, CreatePage *cPage, int nbElements) {
    SDL_Rect nullBtn = {0};

    TextRender textRender;

    if (cPage->page != 0) {

        cPage->pageButtons[0] = createRect(app, wRatio16(app, 0.7), hRatio9(app, 0.4), wRatio16(app, 8.5), hRatio9(app, 7.25), cPage->pageBColor);

        renderTextToPageButtons(app, &textRender, cPage->pageButtons[1], cPage->next);
    } else {
        cPage->pageButtons[0] = nullBtn;
    }

    if (cPage->nbElementsPage * (cPage->page + 1) < cPage->nbTotalElements) {

        cPage->pageButtons[1] = createRect(app, wRatio16(app, 0.7), hRatio9(app, 0.4), wRatio16(app, 10.5), hRatio9(app, 7.25), cPage->pageBColor);

        renderTextToPageButtons(app, &textRender, cPage->pageButtons[1], cPage->before);
    } else {
        cPage->pageButtons[1] = nullBtn;
    }
}

void renderTextToPageButtons(App *app, TextRender *textRender, SDL_Rect pageButton, char *text){
    textRender->length = strlen(text);
    textRender->rect.w = pageButton.w / 1.25;
    textRender->rect.h = pageButton.h / 1.25;
    textRender->rect.w = getAppropriateXOrY(textRender->rect.w, pageButton.w, pageButton.x);
    textRender->rect.w = getAppropriateXOrY(textRender->rect.h, pageButton.h, pageButton.y);

    renderText(app, textRender->rect, app->config.fontCambriab, text, 30, TEXT_BLENDED, app->colors.black);
}

void displayCard (App *app, CreateInfo *cInfo,CreateButtons *cButtons){
    SDL_SetRenderDrawColor(app->renderer, 200, 200, 200, 200);
    SDL_RenderClear(app->renderer);

    SDL_RenderPresent(app->renderer);
}
