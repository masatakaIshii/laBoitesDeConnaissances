/*
** Filename : mysqlQuit.c
**
** Made by  : Masataka ISHII
**
** Description  : functions to free all memory allocation concern to MYSQL API
*/
#ifndef MYSQL_QUIT_FUNCTIONS
#include <stdio.h>
#include <stdlib.h>
#include "../struct.h"

void freeSelectQuery(SelectQuery *selectQuery);
void freeResultStringTable(char ***stringTable, unsigned int numberFields, unsigned int numberRows);
void freeListString(char **fieldsList, unsigned int numberFields);
void freeStructTableMysql(MySqlTable **tables, int numberTables);
void quitStmtManager(MySqlStmtManager *stmtManager);

#endif // MYSQL_QUIT_FUNCTIONS

