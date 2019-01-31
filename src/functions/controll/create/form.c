/*
** Filename : form.c
**
** Made by  : Masataka ISHII
**
** Description  : form functions for events
*/
#include "../../../headers/controll/form.h"

void createForm(App *app, SelectQuery *table, SDL_Rect *listButton, char *tableName, int idParent){
    SDL_Event event;
    TextsInput input;
    MySqlTable tableInfo;
    int done = 0;

    tableInfo = getTable(app, tableName);

    loadTextsInput(&input);

    printf("bienvenue dans le test\n");
    SDL_StopTextInput();
    while (!done) {
        SDL_WaitEvent(&event);
        commonEvents(app, event, &done);
        switch (event.type){
            case SDL_KEYDOWN:
                textInputKeyEvents(event, &input);
            break;

            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT){

                }
            break;

            case SDL_TEXTINPUT:
                textInputEvents(app, event, &input);
            break;
        }
        displayInput(app, &input);
    }
    deleteAllListInputText(input.listChar);
}

void removeCharBeforeCursor(TextsInput *input){
//    printf("ca passe\n");
//    if (input->size > 0 || input->cursor > 0){
//        input->texts[input->size - 1] = '\0';
//        input->cursor--;
//        printf("in removeCharBeforeCursor, text : %s\n", input->texts);
//    }
}

void displayInput(App *app, TextsInput *input){

    ListInputText *list = input->listChar;
    double step = 0.5;
    int i = 0;

    SDL_SetRenderDrawColor(app->renderer, app->colors.blue[0], app->colors.blue[1], app->colors.blue[2], app->colors.blue[3]);
    SDL_RenderClear(app->renderer);

    SDL_Rect buttonInput = createRect(app, wRatio16(app, 8), hRatio9(app, 4.5), wRatio16(app, 4), hRatio9(app, 2.25), app->colors.green);

    if (input->nbChar != 0){

        while(list != NULL){

            list->inputChar.charRect.x = wRatio16(app, 4 + (step * i));
            list->inputChar.charRect.y = hRatio9(app, 3);
            list->inputChar.charRect.w = wRatio16(app, step);
            list->inputChar.charRect.h = hRatio9(app, 1.5);
            renderText(app, list->inputChar.charRect, app->config.fontTimes, list->inputChar.oneChar, 50, TEXT_BLENDED, app->colors.black);
            i++;
            list = list->next;
        }
    }
    showListInputText(input->listChar);
    SDL_RenderPresent(app->renderer);
}

int adaptWForTexts(int wOneChar, int nbChar){
    return wOneChar * nbChar;
}
