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
