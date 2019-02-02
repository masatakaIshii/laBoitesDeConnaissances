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

int verifyInputsValues(App *app, InputManager *inputs, ListFields fields, char* tableName);
Varchar *getInputsValues(inputs, int numberFields);

#endif // VERIFY_FORM
