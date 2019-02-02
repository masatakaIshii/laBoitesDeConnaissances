/*
** Filename : createViewFrom.c
**
** Made by  : Masataka ISHII
**
** Description  : view form functions
*/
#include "../../../headers/view/create/createViewForm.h"
void displayAllForm(App *app, InputManager *input, ListFields fields, char *tableName, SDL_Rect *submitButton){

    //DisplayManager display = displayManagerConstructor(elementHeight, elementWidth, nbColomns, nbRows, startX, startY, stepX, stepY);
    char title[MAX_VARCHAR];
    SDL_Rect titleRect = {wRatio16(app, 5), hRatio9(app, 0.25), wRatio16(app, 6.5), hRatio9(app, 1.25)};

    strcpy(title, "Create your ");
    strcat(title, tableName);
    SDL_SetRenderDrawColor(app->renderer, app->colors.blue[0], app->colors.blue[1], app->colors.blue[2], app->colors.blue[3]);
    SDL_RenderClear(app->renderer);

    createInputs(app, input, fields);

    renderAllForm(app, titleRect, title, submitButton, input, fields);

    //afficher label, input et laisser une place au cas où pour l'error. le sDL_Rect de input doit avoir une bordure

    SDL_RenderPresent(app->renderer);
}


void createInputs(App *app, InputManager *input, ListFields fields){
    int i, j;
    int currentY = hRatio9(app, 2);
    int stepY = hRatio9(app, 0.05);
    Uint8 white[4] = {255, 255, 255, 0};
    SDL_Rect commonPos = { wRatio16(app, 3.65), 0, wRatio16(app, 9), hRatio9(app, 0.60)};
    int length = 0;
    int wForStr = commonPos.w;

    for (i = 0; i < fields.numberFields; i++){
        for (j = 0; j < 3; j++){
            if (j == 0 || j == 2){
                length = strlen(fields.list[i]);
                wForStr = getAppropriateWidth(commonPos, length, input->textInput.maxLength);
                input[i].rectInputs[j] = createRect(app, wForStr, commonPos.h, commonPos.x, currentY, app->colors.blue);
                wForStr = commonPos.w;
            }
            if (j == 1){
                input->textInput.firstRect = getPositionOfText(input[i].rectInputs[j], input[i].textInput.maxLength);
                input[i].rectInputs[j] = createRect(app, commonPos.w, commonPos.h, commonPos.x, currentY, white);
            }
            currentY += commonPos.h;
        }
        currentY += (stepY * 2);
    }
}

/**
*@brief functino to get appropriate text size depend to input size
*
*@param (SDL_Rect) inputRect : input that contain the text
*@param (int) maxLength : the max lengths of texts
*@return (SDL_Rect) textRect : appropriate rect of one char
*/
SDL_Rect getPositionOfText(SDL_Rect inputRect, int maxLength){
    SDL_Rect textRect;
    int marginX = inputRect.x / (maxLength + 2);
    int marginY = inputRect.y / 18;

    textRect.x = inputRect.x + marginX;
    textRect.y = inputRect.y + marginY;
    textRect.w = marginX;
    textRect.h = inputRect.h - (marginY * 2);

    return textRect;
}

/**
*If string length is not null, then get appropriate width
*@param (SDL_Rect) commonRect : structure rect correspond to one part of input
*@param (int) length : string length
*@param (int) maxLength : max length that accept the input
*
*@return (int) appropriate width.
*/
int getAppropriateWidth(SDL_Rect commonRect, int length, int maxLength){
    if (length != 0){
        return commonRect.w / maxLength * length;
    } else {
        return commonRect.w;
    }
}

void renderAllForm(App *app, SDL_Rect titleRect, char *title, SDL_Rect *submitButton, InputManager *input, ListFields fields){
    int i;
    SDL_Rect textSubmit;

    for (i = 0; i < fields.numberFields; i++){
        renderText(app, input[i].rectInputs[0], app->config.fontCambriab, fields.list[i], 50, TEXT_BLENDED, app->colors.black);
    }
    textSubmit.h = hRatio9(app, 1);
    textSubmit.w = wRatio16(app, 2);
    textSubmit.y = hRatio9(app, 7.5);
    textSubmit.x = wRatio16(app, 7);

    *submitButton = createRect(app, wRatio16(app, 2.3), hRatio9(app, 1), wRatio16(app, 6.85), hRatio9(app, 7.5), app->colors.lightblue);

    SDL_RenderFillRect(app->renderer, submitButton);

    renderText(app, textSubmit, app->config.fontCambriab, "submit", 75, TEXT_BLENDED, app->colors.black);
    renderText(app, titleRect, app->config.fontCambriab, title, 100, TEXT_BLENDED, app->colors.white);
}
