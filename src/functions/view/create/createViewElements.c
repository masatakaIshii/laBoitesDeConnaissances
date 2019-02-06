/*
** Filename : createViewElements.c
**
** Made by  : Masataka ISHII
**
** Description  : view elements functions
*/

#include "../../../headers/view/create/createViewElements.h"

void displayElements(App *app, SelectQuery *elements, CreateInfo *cInfo, CreateButtons *cButtons, CreatePage *cPages, char *tableName) {

    int elementHeight = hRatio9(app, 1.25),     elementWidth = wRatio16(app, 1.25);
    int nbColomns = 3,                          nbRows = 2;
    int startX = wRatio16(app, 5.5),            startY = hRatio9(app, 2.75);
    int stepX = wRatio16(app, 3.5),             stepY = hRatio9(app, 0.25);

    DisplayManager display = displayManagerConstructor(elementHeight, elementWidth, nbColomns, nbRows, startX, startY, stepX, stepY);

    SDL_SetRenderDrawColor(app->renderer, cPages->mainPColor[0], cPages->mainPColor[1], cPages->mainPColor[2], cPages->mainPColor[3]);
    SDL_RenderClear(app->renderer);

    displayElementInfo(app, cInfo, tableName);

    // Creating elements
    cPages->nbElementsPage = createCustumElementsPage(app, elements, cButtons, cPages, display);

    // Creating Buttons create and delete
    putButtonsUpperName(cButtons, tableName, "CREATE ", "DELETE ");

    displayPageButtons(app, cPages, display.nbElements);

    displayManageButtons(app, cButtons);

    SDL_RenderPresent(app->renderer);
}

void displayElementInfo(App *app, CreateInfo *cInfo, char *tableName){
    if (strcmp(tableName, "box") == 0){
        displayBoxInfo(app, cInfo);
    } else if (strcmp(tableName, "list") == 0 || strcmp(tableName, "card") == 0){
        displayListOrCard(app, cInfo);
    } else {

    }
}

void displayBoxInfo(App *app, CreateInfo *cInfo){
    cInfo->titleRect.h = hRatio9(app, 1.25);
    cInfo->titleRect.w = wRatio16(app, 8.5);
    cInfo->titleRect.x = getAppropriateXOrY(cInfo->titleRect.w, app->config.width, 0);
    cInfo->titleRect.y = hRatio9(app, 0.25);

    renderText(app, cInfo->titleRect, app->config.fontCambriab, cInfo->title, 77, TEXT_BLENDED, app->colors.white);
}

void displayListOrCard(App *app, CreateInfo *cInfo){
    cInfo->titleRect.h = hRatio9(app, 1.25);
    cInfo->titleRect.w = wRatio16(app, 8.5);
    cInfo->titleRect.x = getAppropriateXOrY(cInfo->titleRect.w, app->config.width, 0);
    cInfo->titleRect.y = hRatio9(app, 0.25);

    renderText(app, cInfo->titleRect, app->config.fontCambriab, cInfo->title, 77, TEXT_BLENDED, app->colors.white);

    cInfo->dateRect.h = hRatio9(app, 0.75);
    cInfo->dateRect.w = wRatio16(app, 8.5);
    cInfo->dateRect.x = getAppropriateXOrY(cInfo->dateRect.w, app->config.width, 0);
    cInfo->dateRect.y = cInfo->titleRect.y + cInfo->titleRect.h;

    renderText(app, cInfo->dateRect, app->config.fontCambriab, cInfo->datetime, 77, TEXT_BLENDED, app->colors.white);
}

void putButtonsUpperName(CreateButtons *cButtons, char *tableName, char *buttonsText0, char *buttonsText1){
    int i = 0;
    char temp[MAX_VARCHAR] = "";
    char temp2[MAX_VARCHAR] = "";
    char temp3[MAX_VARCHAR] = "";

    strcpy(temp, tableName);
    strcpy(temp2, buttonsText0);
    strcpy(temp3, buttonsText1);

    while(temp[i]){
        temp[i] = toupper(temp[i]);
        i++;
    }

    strcpy(cButtons->buttonText0, strcat(temp2, temp));
    strcpy(cButtons->buttonText1, strcat(temp3, temp));
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

        cPage->pageButtons[0] = createRect(app, wRatio16(app, 1), hRatio9(app, 0.65), wRatio16(app, 8.5), hRatio9(app, 7.25), cPage->pageBColor);

        renderTextToButtons(app, &textRender, cPage->pageButtons[1], cPage->before, 1.375, 1.5, app->colors.black);
    } else {
        cPage->pageButtons[0] = nullBtn;
    }

    if (cPage->nbElementsPage * (cPage->page + 1) < cPage->nbTotalElements) {

        cPage->pageButtons[1] = createRect(app, wRatio16(app, 1), hRatio9(app, 0.65), wRatio16(app, 10.5), hRatio9(app, 7.25), cPage->pageBColor);

        renderTextToButtons(app, &textRender, cPage->pageButtons[1], cPage->next, 1.375, 1.5, app->colors.black);
    } else {
        cPage->pageButtons[1] = nullBtn;
    }
}

/**
*@brief : fonction to put text in rect
*@param (App*) app : structure of application
*@param (TextRender*) textRender : structure to help render the text
*@param (SDL_Rect) button : the page that have to contain text
*@param (double) coefW : the coef of reduction width of text compared to rect
*@param (double) coefH : the coef of reduction hight of text compared to rect
*/
void renderTextToButtons(App *app, TextRender *textRender, SDL_Rect button, char *text, double coefW, double coefH, SDL_Color color){
    textRender->length = strlen(text);
    textRender->rect.w = button.w / coefW;
    textRender->rect.h = button.h / coefH;
    textRender->rect.x = getAppropriateXOrY(textRender->rect.w, button.w, button.x);
    textRender->rect.y = getAppropriateXOrY(textRender->rect.h, button.h, button.y);

    renderText(app, textRender->rect, app->config.fontCambriab, text, 50, TEXT_BLENDED, color);
}

void displayManageButtons(App *app, CreateButtons *cButtons) {

    TextRender textRender;

    cButtons->manageButtons[0] = createRect(app, wRatio16(app, 3), hRatio9(app, 1.5), wRatio16(app, 1),  hRatio9(app, 2.75), app->colors.lightblue);

    renderTextToButtons(app, &textRender, cButtons->manageButtons[0], cButtons->buttonText0, 1.25, 1.25, app->colors.black);

    cButtons->manageButtons[1] = createRect(app, wRatio16(app, 3), hRatio9(app, 1.5), wRatio16(app, 1), hRatio9(app, 4.75), app->colors.red);

    if (cButtons->activeDel == 0){
        renderTextToButtons(app, &textRender, cButtons->manageButtons[1], cButtons->buttonText1, 1.25, 1.25, app->colors.black);
    } else {
        renderTextToButtons(app, &textRender, cButtons->manageButtons[1], cButtons->buttonText1, 1.25, 1.25, app->colors.white);
    }

}


void displayCard (App *app, CreateInfo *cInfo, CreateButtons *cButtons){
    int h = hRatio9(app, 1.5);
    int w = wRatio16(app, 0.2);
    int y = hRatio9(app, 0.5);
    showCard pFChard[4] = {displayTitleCard, displayQuestionCard, displayAnswerCard, displayDateTimeCard};
    int i;

    SDL_SetRenderDrawColor(app->renderer, 200, 200, 200, 200);
    SDL_RenderClear(app->renderer);

    renderText(app, cInfo->titleRect, app->config.fontCambriab, cInfo->title, 77, TEXT_BLENDED, app->colors.black);
    for (i = 0; i < 4; i++){
        pFChard[i](app, cInfo, h, w, y);
        y += h;
    }


    SDL_RenderPresent(app->renderer);
}


void displayTitleCard(App *app, CreateInfo *cInfo, int h, int w, int y){
    cInfo->titleRect.h = h;
    cInfo->titleRect.w = w * strlen(cInfo->title);
    cInfo->titleRect.x = getAppropriateXOrY(cInfo->titleRect.w, app->config.width, 0);
    cInfo->titleRect.y = y;

    renderText(app, cInfo->titleRect, app->config.fontCambriab, cInfo->title, 77, TEXT_BLENDED, app->colors.black);
}

void displayQuestionCard(App *app, CreateInfo *cInfo, int h, int w, int y){
    cInfo->questionRect.h = h;
    cInfo->questionRect.w = w * strlen(cInfo->question);
    cInfo->questionRect.x = getAppropriateXOrY(cInfo->questionRect.w, app->config.width, 0);
    cInfo->questionRect.y = y;

    renderText(app, cInfo->questionRect, app->config.fontCambriab, cInfo->question, 77, TEXT_BLENDED, app->colors.black);
}

void displayAnswerCard(App *app, CreateInfo *cInfo, int h, int w, int y){
    cInfo->answerRect.h = h;
    cInfo->answerRect.w = w * strlen(cInfo->answer);
    cInfo->answerRect.x = getAppropriateXOrY(cInfo->answerRect.w, app->config.width, 0);
    cInfo->answerRect.y = y;

    renderText(app, cInfo->answerRect, app->config.fontCambriab, cInfo->answer, 77, TEXT_BLENDED, app->colors.black);
}

void displayDateTimeCard(App *app, CreateInfo *cInfo, int h, int w, int y){
    cInfo->dateRect.h = h;
    cInfo->dateRect.w = w * strlen(cInfo->datetime);
    cInfo->dateRect.x = getAppropriateXOrY(cInfo->dateRect.w, app->config.width, 0);
    cInfo->dateRect.y = y;

    renderText(app, cInfo->dateRect, app->config.fontCambriab, cInfo->datetime, 77, TEXT_BLENDED, app->colors.black);
}
