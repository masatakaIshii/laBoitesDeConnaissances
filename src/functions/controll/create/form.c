/*
** Filename : form.c
**
** Made by  : Masataka ISHII
**
** Description  : form functions for events
*/
#include "../../../headers/controll/form.h"

/**
*@todo : écrire la doc pour chaque fonction de cette page
*@todo : récupérer un tableau de chaîne de caractères correspondant aux valeurs à inscrire dans le formulaire (sans les id et id_ et date)
*@todo : mettre en place un bouton qui prendra en compte un label et l'input texte
*@todo : la liste chaînée de caractère doit être rendu dans l'input texte
*@todo : la liste chaînée ne doit pas dépasser la taille de l'input texte
*/

/**
*function of loop event of form
*
*@param (App *) app : the structure of application
*@param (SelectQuery *) table: adresse of all concerned elements that content in selectQuery
*@param (SDL_Rect *) listButton : list of all button correponded to select query
*@param (
*/
void createForm(App *app, SelectQuery *table, SDL_Rect *listButton, char *tableName, int idParent){
    SDL_Event event;
    MySqlTable tableInfo;

    int done = 0;

    tableInfo = getTable(app, tableName);
    initTextsInput(&input);

    printf("bienvenue dans le test\n");
    SDL_StopTextInput();
    while (!done) {
        SDL_WaitEvent(&event);

        commonEvents(app, event, &done);

        eventForm(app, event, &done)

        displayInput(app, &input);
    }
    deleteAllListInputText(input.listChar);
}

int eventForm(SDL_Event *event, int *done){
    int checkForm = 0;

    switch (event->type){
        case SDL_KEYDOWN:
            textInputKeyEvents(event, &input);
        break;

        case SDL_MOUSEBUTTONDOWN:
            if(event->button.button == SDL_BUTTON_LEFT){

            }
        break;

        case SDL_TEXTINPUT:
            textInputEvents(app, event, &input);
        break;
    }

    return checkForm;
}
