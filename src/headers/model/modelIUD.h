/*
** Filename : mysqlIUD.c
**
** Made by  : Masataka ISHII
**
** Description  : insert, update and delete functions used API C MySQL for select data in database
*/

#ifndef MYSQL_IUD_FUNCTIONS
#include <stdio.h>
#include "modelCommon.h"
#include "modelBindHelper.h"
#include "modelQuit.h"

int queryIUD(App *app, const char *currentQuery);
int preparedQueryIUD(App *app, const char *currentQuery, char **tableNames, int numberTables, char **paramsName, char **paramsValues,  int numberParams);

#endif // MYSQL_IUD_FUNCTIONS
