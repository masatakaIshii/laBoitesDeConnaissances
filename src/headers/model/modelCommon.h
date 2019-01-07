/*
** Filename : modelCommon.c
**
** Made by  : Masataka ISHII
**
** Description  : common functions used API C MySQL
*/

#ifndef MYSQL_COMMON_FUNCTIONS
#include "../struct.h"
#include "../common.h"
#include "modelQuit.h"

void verifyMYSQLIntResult(App *app, int result);
void verifyMYSQLRes(App *app, MYSQL_RES *result);

void verifyPointerForQueryStmt(App *app, MySqlStmtManager *stmtManager, void *pointer, const char *message);
void verifyStmtIntResult(App *app, MySqlStmtManager *stmtManager, char *message, int result);

void verifyResultFile(App *app, int result, int nmemb, const char *message);

Varchar *getFieldsName(App *app, Varchar table, unsigned int* numberFields, unsigned int **listMysqlType);
Varchar *fetchFieldsName(App *app, MYSQL_RES *result, unsigned int numberFields, unsigned int **listMysqlType);
char ***mallocStringTable(unsigned int numberRows,unsigned int numberFields);
char **copyListFields(App *app, Varchar *listFields, unsigned int numberFields);
char **copyListString(App *app, char **listString, unsigned int numberFields);

#endif // MYSQL_COMMON_FUNCTIONS
