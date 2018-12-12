/*
** Filename : modelBindHelper.c
**
** Made by  : Masataka ISHII
**
** Description  : functions used API C MySQL for bind prepared queries
*/

#ifndef MYSQL_BINDHELPER_FUNCTIONS
#include "../struct.h"

short numberOfQMarkAndParamsIsEqual(const char *query, int numberParams);

MYSQL_BIND *bindParams(App *app, char **tableNames, char **paramsName, char **paramsValues, int numberTables, int numberParams);
TableMysql *loadTablesStruct(char **listTables, int numberTables);

#endif // MYSQL_BINDHELPER_FUNCTIONS
