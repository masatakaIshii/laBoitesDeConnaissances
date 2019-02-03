/*
** Filename : verifyForm.c
**
** Made by  : Masataka ISHII
**
** Description  : functions to verify the values in form functions
*/
#include "../../../headers/controll/create/verifyForm.h"

int verifyInputsValues(App *app, InputManager *inputs, ListFields fields, QueryForm *qForm){

/**
*@todo : vérification de chaque valeurs en fonction de leurs types
*@todo : s'il y a une erreur sur un input, alors indiquer l'erreur sur la chaine de la structure InputManager
*@todo : sinon envoie de la requête
*/
    qForm->values = getInputsValues(inputs, fields.numberFields);
    int check = 0; // if error => 0, else => 1

    //check = verifyIfValuesAreCorrects(inputsValues, fields);

    return check;
}

Varchar *getInputsValues(InputManager *inputs, int numberFields){

    Varchar *inputsValues = malloc(sizeof(Varchar) * numberFields);
    ListInputText *temp = NULL;
    int i;

    for (i = 0; i < numberFields; i++){
        temp = inputs[i].textInput.listChar;
        strcpy(inputsValues[i], "");
        while(temp != NULL){
            strcat(inputsValues[i], temp->inputChar.oneChar);
            temp = temp->next;
        }
    }

    return inputsValues;
}


