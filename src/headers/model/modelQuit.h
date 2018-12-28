/*
** Filename : modelQuit.c
**
** Made by  : Masataka ISHII
**
** Description  : functions to free all memory allocation concern to MYSQL API
*/
#ifndef MYSQL_QUIT_FUNCTIONS
#include "../struct.h"

void freeSelectQuery(SelectQuery *selectQuery);
void freeResultStringTable(char ***stringTable, unsigned int numberFields, unsigned int numberRows);
void freeListString(Varchar **fieldsList);
void freeStructTableMysql(Model *model);

void quitModel(Model *model);
void quitStmtManager(MySqlStmtManager *stmtManager);
void quitSelectQuery(SelectQuery *selectQuery);

#endif // MYSQL_QUIT_FUNCTIONS

