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
int sendPreparedQueryIUD(App *app, const char *currentQuery);

#endif // MYSQL_IUD_FUNCTIONS
