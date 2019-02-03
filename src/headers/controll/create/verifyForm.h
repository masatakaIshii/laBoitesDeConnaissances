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
#include "../../model/modelHelper/modelQuit.h"

int verifyInputsValues(App *app, InputManager *inputs, ListFields fields, QueryForm *qForm);
Varchar *getInputsValues(InputManager *inputs, int numberFields);

#endif // VERIFY_FORM
