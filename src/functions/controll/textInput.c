/*
** Filename : textInput.c
**
** Made by  : Masataka ISHII
**
** Description  : text input function functions
*/
#include "../../headers/controll/textInput.h"

/**
*@brief To initialize the structure TextInput
*@param (TextInput *) input
*/
void initTextsInput(TextsInput *input){
    input->cursor = 0;
    input->nbChar = 0;
    input->size = 0;
    input->start = 0;
    input->end = 0;
    input->listChar = NULL;
}

/**
*function for key event for text input\n
*@param (SDL_Event *) event :
*
*
*/
void textInputKeyEvents(SDL_Event *event, TextsInput *input){

    if (event->key.keysym.sym == SDLK_RETURN || event->key.keysym.sym == SDLK_KP_ENTER){

    } else if (event->key.keysym.sym == SDLK_BACKSPACE){
        if (SDL_IsTextInputActive()) {
            int sizeOfChar = 0;
            input->listChar = deleteEndTextInput(input->listChar, &sizeOfChar);
            if (sizeOfChar != 0){
                input->size -= sizeOfChar;
                input->nbChar--;
                input->cursor--;
            }
        }

    } else {
        input->action = ADD_CHAR;
    }
}

/**
*function to activate text input event if there are one click is in one of all inputs, else desactivate\n
*it indicate also which input is activate
*@param (App *) app : structure of application
*@param (SDL_Event *) event : the event of SDL2 to get position of click
*@param (InputManager *) inputs : structure contain all infos of inputs
*@param (int) numberFields : number of fields to insert
*/
void textInputButtonLeftEvents(App *app, SDL_Event *event, InputManager *inputs, int numberFields){
    int i = 0;
    int change = -1;

    for (i = 0; i < numberFields; i++){

        if (inRect(inputs[i].rectInputs[0], event->button.x, event->button.y) || inRect(inputs[i].rectInputs[1], event->button.x, event->button.y)){
            if (SDL_IsTextInputActive() == SDL_FALSE){
                SDL_StartTextInput();
            }

            inputs[i].active = 1;
            change = i;
        } else {
            inputs[i].active = 0;
        }
    }

    if (change == -1){
        for (i = 0; i < numberFields; i++){
            inputs[i].active = 0;
        }
        if (SDL_IsTextInputActive()){
            SDL_StopTextInput();
        }
    }
}

/**
*function related just for text input event\n
*@param (App *) app : structure of application
*@param (SDL_Event *) event : the event of SDL2 to get position of click
*@param (TextsInput *) input : structure for manage text input and output
*/
void textInputEvents(App *app, SDL_Event *event, TextsInput *input){

    if (input->action == ADD_CHAR && input->maxLength > input->nbChar){
        input->listChar = addListInputTextInEnd(app, NULL, event->text.text, input->listChar);
        input->nbChar++;
        input->cursor++;
        input->size+=strlen(event->text.text);
    }
    printf("nbChar : %d\n", input->nbChar);
}

void displayInput(App *app, TextsInput input, Uint8 *rectColor, SDL_Rect textPos){

    ListInputText *list = input.listChar;
    int i = 0;

    if (input.nbChar != 0){

        while(list != NULL){

            list->inputChar.charRect.x = textPos.x + textPos.w * i;
            list->inputChar.charRect.y = textPos.y;
            list->inputChar.charRect.w = textPos.w;
            list->inputChar.charRect.h = textPos.h;
            renderText(app, list->inputChar.charRect, app->config.fontTimes, list->inputChar.oneChar, 50, TEXT_BLENDED, app->colors.black);
            i++;
            list = list->next;
        }
    }
}

int adaptWForTexts(int wOneChar, int nbChar){
    return wOneChar * nbChar;
}
