/*
** Filename : createViewFrom.c
**
** Made by  : Masataka ISHII
**
** Description  : view form functions
*/
#include "../../../headers/view/create/createViewForm.h"
void displayAllForm(App *app, InputManager *inputs, ListFields fields, char *tableName, SDL_Rect *submitButton){

    //DisplayManager display = displayManagerConstructor(elementHeight, elementWidth, nbColomns, nbRows, startX, startY, stepX, stepY);
    char title[MAX_VARCHAR];
    SDL_Rect titleRect = {wRatio16(app, 5), hRatio9(app, 0.25), wRatio16(app, 6.5), hRatio9(app, 1.25)};

    strcpy(title, "Create your ");
    strcat(title, tableName);
    SDL_SetRenderDrawColor(app->renderer, app->colors.blue[0], app->colors.blue[1], app->colors.blue[2], app->colors.blue[3]);
    SDL_RenderClear(app->renderer);

    createInputs(app, inputs, fields);

    renderAllForm(app, titleRect, title, submitButton, inputs, fields);

    displayAllTextInputs(app, inputs, fields.numberFields);

    //afficher label, input et laisser une place au cas où pour l'error. le sDL_Rect de input doit avoir une bordure
}


void createInputs(App *app, InputManager *inputs, ListFields fields){
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
                length = (j == 0) ? strlen(inputs[i].label) : strlen(inputs[i].error);
                wForStr = getAppropriateWidth(commonPos, length, inputs[i].textInput.maxLength);
                inputs[i].rectInputs[j] = createRect(app, wForStr, commonPos.h, commonPos.x, currentY, app->colors.blue);
                wForStr = commonPos.w;
            }
            if (j == 1){
                inputs[i].textInput.firstRect = getPositionOfText(inputs[i].rectInputs[j], inputs[i].textInput.maxLength);
                inputs[i].rectInputs[j] = createRect(app, commonPos.w, commonPos.h, commonPos.x, currentY, white);
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

    int wChar = inputRect.w /(maxLength + 2);

    textRect.x = inputRect.x + wChar;
    textRect.y = inputRect.y;
    textRect.w = wChar;
    textRect.h = inputRect.h;

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
    SDL_Color red = {255, 0, 0, 0};

    for (i = 0; i < fields.numberFields; i++){
        renderText(app, input[i].rectInputs[0], app->config.fontCambriab, input[i].label, 50, TEXT_BLENDED, app->colors.black);
        if (strlen(input[i].error) > 0){
            renderText(app, input[i].rectInputs[2], app->config.fontCambriab, input[i].error, 50, TEXT_BLENDED, red);
        }
    }

    textSubmit.h = hRatio9(app, 1);
    textSubmit.w = wRatio16(app, 2);
    textSubmit.y = hRatio9(app, 7.75);
    textSubmit.x = wRatio16(app, 7);

    *submitButton = createRect(app, wRatio16(app, 2.3), hRatio9(app, 1), wRatio16(app, 6.85), hRatio9(app, 7.75), app->colors.lightblue);

    SDL_RenderFillRect(app->renderer, submitButton);

    renderText(app, textSubmit, app->config.fontCambriab, "submit", 75, TEXT_BLENDED, app->colors.black);
    renderText(app, titleRect, app->config.fontCambriab, title, 100, TEXT_BLENDED, app->colors.white);
}

void displayAllTextInputs(App *app, InputManager *inputs, int numberFields){
    int i;
    Uint8 black[4] = {0, 0, 0, 0};

    for (i = 0; i < numberFields; i++){
        displayInput(app, inputs[i].textInput, black, inputs[i].textInput.firstRect);
    }
}

void displaySuccessForm(App *app, SDL_Rect successButton){
    printf("ca rentre normalement\n");
    Uint8 grey[4] = {192, 192, 192, 0};
    Uint8 white[4] = {255, 255, 255, 255};
    SDL_Color black = {0, 0, 0, 0};
    char *congrate1 = "Congratulation !";
    char *congrate2 = "Your box is successfully created !";
    char *textButton = "Return";
    SDL_Rect frame;
    SDL_Rect congrateText1 = {wRatio16(app, 4), hRatio9(app, 2.25), wRatio16(app, 0.5) * strlen(congrate1), hRatio9(app, 0.5)};
    SDL_Rect congrateText2 = {wRatio16(app, 4), hRatio9(app, 3), wRatio16(app, 0.5) * strlen(congrate2), hRatio9(app, 0.5)};
    SDL_Rect buttonReturn = {wRatio16(app, 7.25), hRatio9(app, 7.15), wRatio16(app, 0.30) * strlen(textButton), hRatio9(app, 1.10)};
    SDL_SetRenderDrawColor(app->renderer, app->colors.blue[0], app->colors.blue[1], app->colors.blue[2], 50);
    SDL_RenderClear(app->renderer);
    frame = createRect(app, wRatio16(app, 8), hRatio9(app, 7.5), wRatio16(app, 4), hRatio9(app, 1.5), grey);
    SDL_RenderFillRect(app->renderer, &frame);
    successButton = createRect(app, wRatio16(app, 3), hRatio9(app, 1.25), wRatio16(app, 8), hRatio9(app, 7), white);

    renderText(app, congrateText1, app->config.fontCambriab, congrate1, 40, TEXT_BLENDED, black);
    renderText(app, congrateText2, app->config.fontCambriab, congrate2, 40, TEXT_BLENDED, black);
    renderText(app, buttonReturn, app->config.fontCambriab, textButton, 40, TEXT_BLENDED, black);
}
