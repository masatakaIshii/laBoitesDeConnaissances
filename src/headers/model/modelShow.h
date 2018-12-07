/*
** Filename : mysqlShow.c
**
** Made by  : Masataka ISHII
**
** Description  : show the result of request
*/

#ifndef MYSQL_SHOW_FUNCTIONS
#include "modelCommon.h"

void showQueryResult(char* ***resultResult,unsigned int* numberFields,unsigned int* numberRows, char **fieldsList);
void addFieldsToResult(char* ***resultQuery, char* **fieldsList, unsigned int* *numberRows);
#endif // MYSQL_SHOW_FUNCTIONS
