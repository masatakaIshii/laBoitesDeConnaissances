/*
** Filename : modelSelect.c
**
** Made by  : Masataka ISHII
**
** Description  : select functions used API C MySQL for select data in database
*/
#ifndef MYSQL_SELECT_FUNCTIONS
#include "modelCommon.h"
#include "../struct.h"
void getSelectQuery (App *app, const char *currentQuery, SelectQuery *selectQuery);
void fetchFieldsOfQuerySelect(App *app, SelectQuery *selectQuery);
short checkIfQueryConcernMoreThan1Table(MYSQL_FIELD *fields, int numberFields);
void fetchQuerySelect(App *app, SelectQuery *selectQuery);
void fetchOneRowQuerySelect(App *app, SelectQuery *selectQuery, unsigned long *lengths, MYSQL_ROW row, int i);
void addFieldsToResult(App *app, SelectQuery *selectQuery);
char **copyListString(App *app, char **listString, unsigned int numberFields);
#endif
