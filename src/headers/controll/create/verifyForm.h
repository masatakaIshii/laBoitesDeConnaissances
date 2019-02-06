/*
** Filename : verifyForm.h
**
** Made by  : Masataka ISHII
**
** Description  : functions to verify the values in form functions
*/

#ifndef VERIFY_FORM

#include "../../common.h"
#include "../../struct.h"
#include "../../model/formModel.h"
#include "../../model/modelHelper/modelQuit.h"

typedef int(*checkValue)(InputManager*, Varchar);

int verifyInputsValues(App *app, InputManager *inputs, ListFields fields, QueryForm *qForm);
Varchar *getInputsValues(InputManager *inputs, int numberFields);

int verifyIfValuesAreCorrects(InputManager *inputs, ListFields fields, Varchar *inputValues);
checkValue *loadCheckValues(InputManager *inputs, ListFields fields);
int verifyIfValuesAreCorrects(InputManager *inputs, ListFields fields, Varchar *inputsValues);
int verifyColor(InputManager *inputs, Varchar inputValue);
int verifyString(InputManager *inputs, Varchar inputValue);

Varchar *getValuesToSend(InputManager *inputs, QueryForm *qForm, Varchar *inputsValues, int numberInputs);
#endif // VERIFY_FORM
