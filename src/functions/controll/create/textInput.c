/*
** Filename : textInput.c
**
** Made by  : Masataka ISHII
**
** Description  : text input function functions
*/
#include "../../../headers/controll/textInput.h"

/**
*to initialize the text input
*
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
*
*
*
*
*/
void textInputKeyEvents(SDL_Event event, TextsInput *input){

    if (event.key.keysym.sym == SDLK_F1){
        SDL_StartTextInput();
        printf("SDL_TextInput activate\n");
    }

    if (event.key.keysym.sym == SDLK_F2){
        if (SDL_IsTextInputActive()){
            SDL_StopTextInput();
            printf("SDL_TextInput desactivate\n");
        }
    }
    if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER){

    } else if (event.key.keysym.sym == SDLK_RIGHT){
        (input->cursor <= input->nbChar) ? input->cursor++ : 0;

    } else if (event.key.keysym.sym == SDLK_LEFT){
        (input->cursor > 0) ? input->cursor-- : 0;

    } else if (event.key.keysym.sym == SDLK_DELETE){
        input->action = (input->cursor < input->nbChar) ?  R_DELETE : STAND_BY;

    } else if (event.key.keysym.sym == SDLK_BACKSPACE){
        if (SDL_IsTextInputActive()) {
            int sizeOfChar = 0;
            input->listChar = deleteEndTextInput(input->listChar, &sizeOfChar);
            if (sizeOfChar != 0){
                input->size -= sizeOfChar;
                input->nbChar--;
                input->cursor--;
            }
            printf("sizeOfChar : %d\n", sizeOfChar);
            printf("input->size : %d\n", input->size);
        }

    } else {
        input->action = ADD_CHAR;
    }
}


void textInputEvents(App *app, SDL_Event *event, TextsInput *input){

    if (input->action == ADD_CHAR){
        input->listChar = addListInputTextInEnd(app, NULL, event->text.text, input->listChar);
        input->nbChar++;
        input->cursor++;
        input->size+=strlen(event->text.text);
    }
}

void displayInput(App *app, TextsInput *input, Uint8 *rectColor, SDL_Rect rectInput, SDL_Rect textPos){

    ListInputText *list = input->listChar;
    int i = 0;

    SDL_Rect buttonInput = createRect(app, rectInput.w, rectInput.h, rectInput.x, rectInput.y, rectColor);

    if (input->nbChar != 0){

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
    showListInputText(input->listChar);
    SDL_RenderPresent(app->renderer);
}

int adaptWForTexts(int wOneChar, int nbChar){
    return wOneChar * nbChar;
}
