/*
** Filename : formTest.c
**
** Made by  : Masataka ISHII
**
** Description  : test form functions
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <mysql.h>
#include "../../headers/common.h"
#include "../../headers/controll/test.h"

/**
*@todo : gérer saisie de clavier pour afficher caractères
*@todo : afficher les saisie au rendu
*@todo : gérer le focus, cad qu'il faut que l'input soit cliquer pour que son focus = 1, et après il est possible de faire des saisies.
*@todo : modifier la largeur du rectanble :+ taille char à  l'ajour, -taille char à la suppression
*@todo : cursor qui permet de déterminer quelle emplacement se passera ajout ou suppression
*@todo : déplacement du cursor avec flèches directionnelles droite et gauche
*@todo : si le cursor fait dépasse la limite du rectangle contenant l'input, il ne peut plus se déplacer
*@todo : (si ca avance bien) : si la taille du nombre de caractère dépasse celui de l'input, déplacement de l'ensemble.
            si le dépassement se passe à droite : beginChar+1 et endChar+1
*@todo : si la taille du string a dépassé et qu'il y a un char de supprimer en fin de chaine: beginChar-1 et endChar-1
*@todo : si le dépassement de la taille du nombre de caractère visible est dépassé, :
            -si le cursor est au coin à droite et se déplace à droite : beginChar+1 et endChar+1
            -si le cursor est au coin à gauche et se dépalce à gauche : beginChar-1 et endChar-1;

*@todo : au double click sur l'input texte, une selection totale est indiqué : si la prochaine saisie est
*/

int testEventLoop(App *app) {
    SDL_Event event;
    int done = 0;
    short startInput = 0;
    TextsInput input = {"", 0};
    SDL_Rect buttonInput;

    printf("bienvenue dans le test\n");
    SDL_StopTextInput();
    while (!done) {
        SDL_WaitEvent(&event);
        commonEvents(app, event, &done);
        switch (event.type){
            case SDL_KEYDOWN:
                // MODE PLAY
                textInputKeyEvents(event, &input, &startInput);
                // Fonction CREATE
            break;

            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT){

                }
            break;

            case SDL_TEXTINPUT:

                textInputEvents(app, event, &input);

            break;
        }
        displayInput(app, buttonInput, &input);
    }

    return (done) ? EXIT_SUCCESS : EXIT_FAILURE;
}

void textInputKeyEvents(SDL_Event event, TextsInput *input, short *startInput){

    input->length = strlen(input->texts);

    if (event.key.keysym.sym == SDLK_F1){
        SDL_StartTextInput();
        printf("SDL_TextInput activate\n");
        *startInput = 1;
    }

    if (event.key.keysym.sym == SDLK_F2){
        if (SDL_IsTextInputActive()){
            SDL_StopTextInput();
            printf("SDL_TextInput desactivate\n");
        }
    }
    if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER){

    } else if (event.key.keysym.sym == SDLK_RIGHT){
        (input->cursor <= strlen(input->texts)) ? input->cursor++ : 0;
    } else if (event.key.keysym.sym == SDLK_LEFT){
        (input->cursor > 0) ? input->cursor-- : 0;
    } else if (event.key.keysym.sym == SDLK_DELETE){
        input->action = (input->cursor < strlen(input->texts)) ?  R_DELETE : STAND_BY;
    } else if (event.key.keysym.sym == SDLK_BACKSPACE){
        (SDL_IsTextInputActive()) ? removeCharBeforeCursor(input) : printf("ca ne passe pas!\n");
    } else {
        input->action = ADD_CHAR;
    }
}

void textInputEvents(App *app, SDL_Event event, TextsInput *input){

    input->length = strlen(input->texts);
    printf("in textInputsEvents, action : %d\n", input->action);
    if (input->action == ADD_CHAR){
        addCharInInputString(input, event.text.text);
    }

    printf("fullText : %s\n", input->texts);
    printf("input->cursor : %d\n", input->cursor);
}

void addCharInInputString(TextsInput *input, char *oneChar){

    if (input->cursor == input->length || input->length == 0){
        strcat(input->texts, oneChar);
        input->cursor++;
    } else {

    }
}

void removeCharBeforeCursor(TextsInput *input){
    printf("ca passe\n");
    if (input->length > 0 || input->cursor > 0){
        input->texts[input->length - 1] = '\0';
        input->cursor--;
        printf("in removeCharBeforeCursor, text : %s\n", input->texts);
    }
}

void displayInput(App *app, SDL_Rect buttonInput, TextsInput *input){

    input->length = strlen(input->texts);
    SDL_SetRenderDrawColor(app->renderer, app->colors.blue[0], app->colors.blue[1], app->colors.blue[2], app->colors.blue[3]);
    SDL_RenderClear(app->renderer);

    buttonInput = createRect(app, wRatio16(app, 8), hRatio9(app, 4.5), wRatio16(app, 4), hRatio9(app, 2.25), app->colors.green);

    SDL_Rect inputTextRect = {wRatio16(app, 4.5), hRatio9(app, 4), adaptWForTexts(wRatio16(app, 1), input->length), hRatio9(app, 2.25)};

    printf("length : %d\n", input->length);
    if (input->length > 0){
        renderText(app, inputTextRect, app->config.fontTimes, input->texts, 50, TEXT_BLENDED, app->colors.black);
    }

    SDL_RenderPresent(app->renderer);
}

int adaptWForTexts(int wOneChar, int nbChar){
    return wOneChar * nbChar;
}
