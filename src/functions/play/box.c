/*
** Filename : box.c
**
** Made by  : Baptiste LEGO
**
** Description  : box menu main functions
*/

#include "../../headers/common.h"
#include "../../headers/play/box.h"
#include "../../headers/play/list.h"
#include "../../headers/model/boxModel.h"

enum {PREVIOUS, NEXT};

void playMode(App *app){
    SDL_Event event;
    SDL_Rect pageButtons[2];
    SDL_Rect *boxButtons = NULL;
    int nbOfBox = 0;
    int page = 0;
    int done = 0;
    int i = 0;

    // Getting data
    SelectQuery boxes = getBoxes(app);

    boxButtons = malloc(boxes.numberRows * sizeof(SDL_Rect));
    verifyPointer(app, boxButtons, "Can't allocate memory for boxButtons\n");

    // Event loop
    while (!done) {
        SDL_WaitEvent(&event);
        commonEvents(app, event, &done);
        switch (event.type) {
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT){
                    // Change the page
                    if(inRect(pageButtons[PREVIOUS] , event.button.x, event.button.y))
                        page--;
                    else if(inRect(pageButtons[NEXT] , event.button.x, event.button.y))
                        page++;

                    // Display a box
                    for(i = 0; i < nbOfBox; i++){
                        if(inRect(boxButtons[i], event.button.x, event.button.y))
                            listMenu(app, boxes, page, i);
                    }
                }
            break;
        }
        displayHomePlay(app, boxes, page, pageButtons, boxButtons, &nbOfBox);
    }

    free(boxButtons);
}


/*///////////////////////// DISPLAY \\\\\\\\\\\\\\\\\\\\\\\\\\*/


void displayHomePlay(App *app, SelectQuery boxes, int page, SDL_Rect *pageButtons, SDL_Rect *boxButtons, int *nbOfBoxInPage){
    SDL_Rect nullBtn = {0};
    SDL_Rect textPos = {wRatio16(app, 0.5), hRatio9(app, 3), wRatio16(app, 15), hRatio9(app, 2)};

    // Set background color
    SDL_SetRenderDrawColor(app->renderer, app->colors.blue[0], app->colors.blue[1], app->colors.blue[2], app->colors.blue[3]);
    SDL_RenderClear(app->renderer);

    // Write title
    writeTitle(app, "TOUTES LES BOITES");
    writeReturnKey(app);

    if(boxes.numberRows == 0){
        renderText(app, textPos, app->config.fontCambriab, "Aucune boite existante ... Commence par le mode create !", 60, TEXT_BLENDED, app->colors.white);
    }
    else{
        // Creating boxes
        *nbOfBoxInPage = createBoxPage(app, boxes, boxButtons, boxes.numberRows, page);

        // Conditions for page buttons
        if(page != 0){
            pageButtons[PREVIOUS] = createRect(app, app->config.height / 12, app->config.height / 15, (app->config.width / 12) * 5, (app->config.height / 12) * 11, app->colors.green);
            renderText(app, pageButtons[PREVIOUS], app->config.fontCambriab, "<--", 30, TEXT_BLENDED, app->colors.black);
        }
        else
            pageButtons[PREVIOUS] = nullBtn;

        if(10 * (page+1) < boxes.numberRows){
            pageButtons[NEXT] = createRect(app, app->config.height / 12, app->config.height / 15, (app->config.width / 12) * 6, (app->config.height / 12) * 11, app->colors.green);
            renderText(app, pageButtons[NEXT], app->config.fontCambriab, "-->", 30, TEXT_BLENDED, app->colors.black);
        }
        else
            pageButtons[NEXT] = nullBtn;
    }

    SDL_RenderPresent(app->renderer);
}

int createBoxPage(App *app, SelectQuery boxes, SDL_Rect *buttons, int size, int page){
    int x, y, i = 10 * page;
    int xBox = 0, yBox = 0;

    for(x = 0; x < 5; x++){
        for(y = 0; y < 2; y++){
            if(i >= size)
                break;

            // Create square
            xBox = ((app->config.width / 3) * y) + 10*y + app->config.width/5;
            yBox = ((app->config.height / 8) * x) + 10*x + app->config.height/6;
            buttons[i] = createRect(app, app->config.height / 8, app->config.height / 8, xBox, yBox, hexToRgb(boxes.listColumnsRows[i][B_COLOR]));
            renderText(app, buttons[i], app->config.fontTimes, "12", 40, TEXT_BLENDED, app->colors.black);

            // Create texts
            renderButtonLabel(app, boxes.listColumnsRows[i], buttons[i]);
            i++;
        }
        if(i >= size)
            break;
    }

    return i - 10 * page; // Return number of elements printed
}

void renderButtonLabel(App *app, char **data, SDL_Rect buttonPos){
    SDL_Rect textPos = buttonPos;

    // Name of the box
    textPos.x += app->config.height / 8 + 5;
    textPos.h /= 1.5;

    if(strlen(data[NAME]) < 6)
        textPos.w *= 2;
    else if(strlen(data[NAME]) < 12)
        textPos.w *= 3;
    else
        textPos.w *= 4;

    renderText(app, textPos, app->config.fontCambriab, data[NAME], 70, TEXT_BLENDED, app->colors.white);

    // Last modification date
    textPos.y += textPos.h;
    textPos.w = buttonPos.w * 2;
    textPos.h /= 2;
    renderText(app, textPos, app->config.fontCambriab, data[B_MODIFIED_DATE], 50, TEXT_BLENDED, app->colors.white);
}
