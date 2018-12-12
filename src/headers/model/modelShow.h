/*
** Filename : mysqlShow.c
**
** Made by  : Masataka ISHII
**
** Description  : show the result of request
*/

#ifndef MYSQL_SHOW_FUNCTIONS
#include "modelCommon.h"

void showQueryResult(char ****resultQuery, unsigned int *numberFields, unsigned int *numberRows, char **fieldsList);
void addFieldsToResult(char* ***resultQuery, char* **fieldsList, unsigned int* *numberRows);
void showWellResult(char ***resultQuery, int numberFields, int numberRows, char **fieldsList);
int *getMaxLengthOfEachFields(char ***resultQuery, int numberFields, int numberRows);
void addSpaceToGetSameLengthPerField(char ****resultQuery, int numberFields, int numberRows, int *maxLengthsFields);
char *getSpaces(int numberSpace);
#endif // MYSQL_SHOW_FUNCTIONS
