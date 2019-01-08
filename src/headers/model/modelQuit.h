/*
** Filename : modelQuit.c
**
** Made by  : Masataka ISHII
**
** Description  : functions to free all memory allocation concern to MYSQL API
*/
#ifndef MYSQL_QUIT_FUNCTIONS
#include "../struct.h"

void freeSelectQuery(App *app);
void freeResultStringTable(char ****stringTable, unsigned int numberFields, unsigned int numberRows);
void freeListString(Varchar **fieldsList);
void freeStructTableMysql(Model *model);

void quitModel(Model *model);

void quitPreparedIUD(App *app);
void quitPreparedSelectQuery(App *app);

void quitStmtManager(MySqlStmtManager *stmtManager);
void quitStmtParams(MySqlStmtManager *stmtManager);
void quitSelectQuery(SelectQuery *selectQuery);
void quitStmtBind(MySqlStmtManager *stmtManager);
void quitInsertParamFinder(InsertParamFinder *paramFinder);

#endif // MYSQL_QUIT_FUNCTIONS

