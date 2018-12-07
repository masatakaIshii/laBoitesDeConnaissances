/*
** Filename : modelSelect.c
**
** Made by  : Masataka ISHII
**
** Description  : select functions used API C MySQL for select data in database
*/
#ifndef MYSQL_SELECT_FUNCTIONS
#include "modelCommon.h"

char ***querySelect (App *app, const char *currentQuery, unsigned int *numberFields, unsigned int *numberRows);
char ***fetchQuerySelect(MYSQL_RES *result, unsigned int numberFields, unsigned int numberRows);
#endif
