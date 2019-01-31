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
*@todo : g�rer saisie de clavier pour afficher caract�res
*@todo : afficher les saisie au rendu
*@todo : g�rer le focus, cad qu'il faut que l'input soit cliquer pour que son focus = 1, et apr�s il est possible de faire des saisies.
*@todo : modifier la largeur du rectanble :+ taille char �  l'ajour, -taille char � la suppression
*@todo : cursor qui permet de d�terminer quelle emplacement se passera ajout ou suppression
*@todo : d�placement du cursor avec fl�ches directionnelles droite et gauche
*@todo : si le cursor fait d�passe la limite du rectangle contenant l'input, il ne peut plus se d�placer
*@todo : (si ca avance bien) : si la taille du nombre de caract�re d�passe celui de l'input, d�placement de l'ensemble.
            si le d�passement se passe � droite : beginChar+1 et endChar+1
*@todo : si la taille du string a d�pass� et qu'il y a un char de supprimer en fin de chaine: beginChar-1 et endChar-1
*@todo : si le d�passement de la taille du nombre de caract�re visible est d�pass�, :
            -si le cursor est au coin � droite et se d�place � droite : beginChar+1 et endChar+1
            -si le cursor est au coin � gauche et se d�palce � gauche : beginChar-1 et endChar-1;

*@todo : au double click sur l'input texte, une selection totale est indiqu� : si la prochaine saisie est
*/

int testEventLoop(App *app) {
    SDL_Event event;
    int done = 0;
    TextsInput input;

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

    return (done) ? EXIT_SUCCESS : EXIT_FAILURE;
}

void addCharInInputString(TextsInput *input, char *oneChar){

//    if (input->cursor == input->nbChar || input->nbChar == 0){
//        strcat(input->texts, oneChar);
//        input->cursor++;
//    } else {
//
//    }
}

//void displayInput(App *app, TextsInput *input){
//
//    ListInputText *list = input->listChar;
//    double step = 0.5;
//    int i = 0;
//
//    SDL_SetRenderDrawColor(app->renderer, app->colors.blue[0], app->colors.blue[1], app->colors.blue[2], app->colors.blue[3]);
//    SDL_RenderClear(app->renderer);
//
//    SDL_Rect buttonInput = createRect(app, wRatio16(app, 8), hRatio9(app, 4.5), wRatio16(app, 4), hRatio9(app, 2.25), app->colors.green);
//
//    printf("nbChar : %d\n", input->nbChar);
//    printf("size : %d\n", input->size);
//    printf("cursor : %d\n", input->cursor);
//    if (input->nbChar != 0){
//
//        while(list != NULL){
//
//            list->inputChar.charRect.x = wRatio16(app, 4 + (step * i));
//            list->inputChar.charRect.y = hRatio9(app, 3);
//            list->inputChar.charRect.w = wRatio16(app, step);
//            list->inputChar.charRect.h = hRatio9(app, 1.5);
//            renderText(app, list->inputChar.charRect, app->config.fontTimes, list->inputChar.oneChar, 50, TEXT_BLENDED, app->colors.black);
//            i++;
//            list = list->next;
//        }
//    }
//    showListInputText(input->listChar);
//    SDL_RenderPresent(app->renderer);
//}

//int adaptWForTexts(int wOneChar, int nbChar){
//    return wOneChar * nbChar;
//}
