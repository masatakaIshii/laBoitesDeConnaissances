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
    Varchar *inputsValues = getInputsValues(inputs, fields.numberFields);
    int check = 0; // if there are error => 1, else => 0

    check = verifyIfValuesAreCorrects(inputs, fields, inputsValues);

    //qForm->values = getValuesToSend(inputs, fields, inputsValues);

//    inputs[0].error[0] = '\0';

    free(inputsValues);

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

/**
*verify all inputs values if it's correct
*@param (InputManager*) inputs : array of structure to manage input, if value is not correct, put error
*@param (ListFields) fields : structure of inputs linked to the form
*@param (Varchar*) inputsValues : all values of inputs
*/
int verifyIfValuesAreCorrects(InputManager *inputs, ListFields fields, Varchar *inputsValues){
    int i;
    int check = 0;
    int result = 0;
    //checkValue *pCheckValues = loadCheckValues(inputs, fields);

    for (i = 0; i < fields.numberFields; i++){
        verifyColor(&inputs[i], inputsValues[i]);
        if (result == 0 && check == 1){
            result = 1;
        }
    }

    //free(pCheckValues);

    return result;
}

//checkValue *loadCheckValues(InputManager *inputs, ListFields fields){
//    checkValue pFuncCheck = malloc(sizeof(checkValue) * fields.numberFields);
//
//
//}

/**
*@brief function to verify if value of color is correct
*@param (InputManager*) inputs : array of structure to manage input
*@param (int) index : index of current value
*@param (Varchar) inputValue : one of all input value come to form
*/
int verifyColor(InputManager *inputs, Varchar inputValue){

    int check = 0;
    int length = 0;
    int step = 0;
    int i;

    for (step = 0; step < 2 && check == 0; step++){
        switch(step){
        case 0:
            length = strlen(inputValue);
            if (length != 6){
                check = 1;
            }
            break;
        case 1:
            for (i = 0; i < (strlen(inputValue) + 1); i++){
                if ((inputValue[i] >= '0' || inputValue[i] <= '9') || (inputValue[i] >= 'a' || inputValue[i] <= 'f') || (inputValue[i] >= 'A' || inputValue[i] <= 'F')){

                } else {
                    check = 1;
                }
            }
        }
    }
    if (check == 1){
        strcpy(inputs->error, "The color value is not correct");
    } else {
        inputs->error[0] = '\0';
    }

    return check;
}


/**
*Function to get values for the insert query
*@param (InputManager*) inputs : the structure of inputs
*@param (ListFields) fields : structure of fields linked to form
*@param (Varchar*) inputsValues : values of text inputs in form
*/
//Varchar *getValuesToSend(InputManager *inputs, ListFields fields, Varchar *inputsValues){
//
//}


