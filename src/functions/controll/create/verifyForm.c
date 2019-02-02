/*
** Filename : verifyForm.c
**
** Made by  : Masataka ISHII
**
** Description  : functions to verify the values in form functions
*/
#include "../../../headers/controll/create/verifyForm.h"

int verifyInputsValues(App *app, InputManager *inputs, ListFields fields, char* tableName){

/**
*@todo : mettre valeur des inputs dans un tableaux de string
*@todo : vérification de chaque valeurs en fonction de leurs types
*@todo : s'il y a une erreur sur un input, alors indiquer l'erreur sur la chaine de la structure InputManager
*@todo : sinon envoie de la requête
*/
    Varchar *inputsValues = getInputsValues(inputs, fields.numberFields);




    return 0;
}

Varchar *getInputsValues(inputs, int numberFields){

    Varchar *inputsValues = NULL;

}
