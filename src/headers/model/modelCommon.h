/*
** Filename : mysqlCommon.h
**
** Made by  : Masataka ISHII
**
** Description  : common functions used API C MySQL
*/

#ifndef MYSQL_COMMON_FUNCTIONS
#include "../struct.h"
void dbConnect(App *app);
void closeMySQL(App *app);
void verifyMYSQLIntResult(App *app, int result);
void verifyMYSQLRes(App *app, MYSQL_RES *result);
void verifyPointerForQueryStmt(App *app, MySqlStmtManager *stmtManager, void *pointer, const char *message);
char **getFieldsName(App *app, const char *table, unsigned int* numberFields, unsigned int **listMysqlType);
char **fetchFieldsName(App *app, MYSQL_RES *result, unsigned int numberFields, unsigned int **listMysqlType);
char ***mallocStringTable(unsigned int numberRows,unsigned int numberFields);

MYSQL_STMT *stmtInitialisation(App *app);
void loadStmtManager(App *app, MySqlStmtManager *stmtManager, int numberTables, int numberParams, const char *query);
unsigned int getTypeOfField(App *app, char *field, char *table);

#endif // MYSQL_COMMON_FUNCTIONS
