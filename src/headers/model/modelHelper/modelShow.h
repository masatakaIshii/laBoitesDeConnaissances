/*
** Filename : mysqlShow.h
**
** Made by  : Masataka ISHII
**
** Description  : show the result of request
*/

#ifndef MYSQL_SHOW_FUNCTIONS
#include "../../common.h"
#include "modelCommon.h"
#include "modelQuit.h"

void showQueryResult(App *app, SelectQuery *selectQuery);
int *getMaxLengthOfEachFields(App *app, char ***resultQuery, int numberFields, int numberRows);
void showAppropriateQueryResult(SelectQuery *selectQuery, int *maxLengthsFields, int numberFields, int numberRows);
void showLign(SelectQuery *selectQuery, int *maxLengthsFields, int numberFields);
#endif // MYSQL_SHOW_FUNCTIONS
