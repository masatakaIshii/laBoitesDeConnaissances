/*
** Filename : verifyForm.c
**
** Made by  : Masataka ISHII
**
** Description  : functions to verify the values in form functions
*/
#include "../../../headers/controll/create/verifyForm.h"

/**
*@brief main functon to verify inputs values and send query
*@param (App*) app : structure of application
*@param (InputManager*) inputs : structure to manage inputs
*@param (ListFields) fields : fields concerned to the form
*@param (QueryForm*) qForm : structure to send query of form
*@return (int) check : if check is -1 => error, 1 => query send, 0 => nothing
*/
int verifyInputsValues(App *app, InputManager *inputs, ListFields fields, QueryForm *qForm){
    Varchar *inputsValues = getInputsValues(inputs, fields.numberFields);
    int check = 0; // if there are error => 1, else => 0

    check = verifyIfValuesAreCorrects(inputs, fields, inputsValues);

    printf("qForm->query : %s\n", qForm->query);
    qForm->values = getValuesToSend(inputs, qForm, inputsValues, fields.numberFields);

    int i;

    for (i = 0; i < qForm->numberFields; i++){
        printf("fields.list[%d] : %s\n", i, qForm->fields[i]);
        printf("qForm->values[%d] : %s\n",i, qForm->values[i]);
    }
    if (check != -1){
        check = sendInsertQuery(app, qForm);
    }

    free(inputsValues);


    return check;
}

/**
*@brief to put chained lists char to strings Varchar
*@param (InputManager*) inputs : array of structure to manage chained list
*@param (int) numberFields : number of inputs
*@return (Varchar*) inputsValues : get all inputs
*/
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
    checkValue *pCheckValues = loadCheckValues(inputs, fields);

    for (i = 0; i < fields.numberFields; i++){
        check = pCheckValues[i](&(inputs[i]), inputsValues[i]);
        if (result == 0 && check == 1){
            result = -1;
        }
    }

    free(pCheckValues);

    return result;
}

/**
*@brief pointer of function for inputs verifications
*@param (InputManager*) inputs : the structure for manage inputs
*@param (ListFields) fields : the list of fields correspond to the form
*@return (checkValues*) : the array of type checkValue correspond to int(*p)(InputManager*, ListFields)
*/
checkValue *loadCheckValues(InputManager *inputs, ListFields fields){
    checkValue *pFuncCheck = malloc(sizeof(checkValue) * fields.numberFields);
    int i;

    for (i = 0; i < fields.numberFields; i++){
        if (strcmp(fields.list[i], "color") == 0){
            pFuncCheck[i] = verifyColor;
        } else {
            pFuncCheck[i] = verifyString;
        }
    }

    return pFuncCheck;
}

/**
*@brief function to verify if value of color is correct
*@param (InputManager*) inputs : array of structure to manage input
*@param (int) index : index of current value
*@param (Varchar) inputValue : one of all input value come to form
*@return check : 0 => correct, 1 => not correct
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
            for (i = 0; i < (strlen(inputValue)); i++){
                if ((inputValue[i] >= '0' && inputValue[i] <= '9') || (inputValue[i] >= 'a' && inputValue[i] <= 'f') || (inputValue[i] >= 'A' && inputValue[i] <= 'F')){

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
*verify if name value is correct
*@param (InputManager*) inputs : array of structure to manage input
*@param (int) index : index of current value
*@param (Varchar) inputValue : one of all input value come to form
*@return (int) check : 0 => correct, 1 => not correct
*/
int verifyString(InputManager *inputs, Varchar inputValue){
    int check = 0;
    int length = strlen(inputValue);

    if (length > inputs->textInput.maxLength || strlen(inputValue) == 0){
        strcpy(inputs->error, "The name value is not correct");
        check = 1;
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
*@return (Varchar*) qValues : the array of values to affect in qForm->values
*/
Varchar *getValuesToSend(InputManager *inputs, QueryForm *qForm, Varchar *inputsValues, int numberInputs){
    Varchar *qValues = NULL;    // values for the insert query
    Varchar strId;              // if fields have id_parent, the string of this number
    int i;
    int j;
    int index = 0;

    qValues = malloc(sizeof(Varchar) * qForm->numberFields);
    for (i = 0; i < qForm->numberFields; i++){
        // verify if id is "id_..." form

        if (strncmp(qForm->fields[i], "id_", 3) == 0){
            sprintf(strId, "%d", qForm->idParent);
            strcpy(qValues[index],strId);
            printf("strId : %s\n", strId);
            index++;
        } else {
            for (j = 0; j < numberInputs; j++){
                if (strcmp(inputs[j].label, qForm->fields[i]) == 0){
                    strcpy(qValues[index], inputsValues[j]);
                    index++;
                    break;
                }
            }
        }
        // verify if the query field name == label of input

    }

    return qValues;
}


