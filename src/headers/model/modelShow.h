/*
** Filename : mysqlShow.c
**
** Made by  : Masataka ISHII
**
** Description  : show the result of request
*/

#ifndef MYSQL_SHOW_FUNCTIONS
#include "../common.h"
#include "modelCommon.h"
#include "modelQuit.h"

void showQueryResult(App *app);
int *getMaxLengthOfEachFields(App *app, char ***resultQuery, int numberFields, int numberRows);
void copyListQuerySelect(App *app, char ****resultQuery,SelectQuery *selectQuery);
void addSpaceToGetSameLengthPerField(App *app, char ****resultQuery, int numberFields, int numberRows, int *maxLengthsFields);
char *getSpaces(int numberSpace);
#endif // MYSQL_SHOW_FUNCTIONS
