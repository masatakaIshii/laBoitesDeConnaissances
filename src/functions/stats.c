/*
** Filename : stats.c
**
** Made by  : Baptiste LEGO
**
** Description  : stats functions
*/

#include "../headers/common.h"
#include "../headers/stats.h"
#include "../headers/model/boxModel.h"
#include "../headers/model/listModel.h"
#include "../headers/model/cardModel.h"

void stats(App *app){
    SDL_Event event;
    int done = 0;
    SelectQuery boxes, lists, cards;

    // Getting data
    boxes = getBoxes(app);
    lists = getAllLists(app);
    cards = getAllCards(app);

    while (!done) {
        SDL_WaitEvent(&event);
        commonEvents(app, event, &done);
        switch (event.type) {
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT){
                    // Action

                }
            break;
        }
        displayStats(app, boxes, lists, cards);
    }
}

int countRightAnswers(App *app, SelectQuery cards){
    int i, counter = 0;

    for(i = 0; i < cards.numberRows; i++){
        counter += intConvertor(cards.listColumnsRows[i][6]);
    }

    return counter;
}


/*///////////////////////// DISPLAY \\\\\\\\\\\\\\\\\\\\\\\\\\*/


void displayStats(App *app, SelectQuery boxes, SelectQuery lists, SelectQuery cards){
    // Setting background
    SDL_SetRenderDrawColor(app->renderer, app->colors.blue[0], app->colors.blue[1], app->colors.blue[2], app->colors.blue[3]);
    SDL_RenderClear(app->renderer);

    // Write title
    writeTitle(app, "STATISTIQUES");

    writeStats(app, boxes, lists, cards);

    // Refresh screen
    SDL_RenderPresent(app->renderer);
}

void writeStats(App *app, SelectQuery boxes, SelectQuery lists, SelectQuery cards){
    SDL_Rect textPos;

    textPos.x = wRatio16(app, 1);
    textPos.y = hRatio9(app, 2);
    textPos.w = wRatio16(app, 4);
    textPos.h = hRatio9(app, 0.5);
    printNumberStat(app, textPos, "Nombre de boites créées : ", boxes.numberRows);

    textPos.y += hRatio9(app, 1);
    printNumberStat(app, textPos, "Nombre de listes créées : ", lists.numberRows);

    textPos.y += hRatio9(app, 1);
    printNumberStat(app, textPos, "Nombre de cartes créées : ", lists.numberRows);

    textPos.y += hRatio9(app, 1);
    printNumberStat(app, textPos, "Nombre de bonnes réponses : ", countRightAnswers(app, cards));
}

void printNumberStat(App *app, SDL_Rect textPos, char *description, int number){
    char text[100];
    char strNumber[5];

    // Convert int to str
    sprintf(strNumber, "%d", number);

    // Creating final text
    strcpy(text, description);
    strcat(text, strNumber);

    // Render
    renderText(app, textPos, app->config.fontCambriab, text, 50, TEXT_BLENDED, app->colors.white);
}
