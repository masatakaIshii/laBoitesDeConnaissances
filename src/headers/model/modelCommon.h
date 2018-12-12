/*
** Filename : mysqlCommon.h
**
** Made by  : Masataka ISHII
**
** Description  : common functions used API C MySQL
*/

#ifndef MYSQL_COMMON_FUNCTIONS
#include "../struct.h"
#include <winsock2.h>
#include <mysql.h>

void dbConnect(App *app);
void verifyMYSQLPointer(App *app, void *pointer);
void verifyMYSQLIntResult(App *app, int result);

char **getFieldsName(App *app, const char *table, unsigned int* numberFields, unsigned int **listMysqlType);
char **fetchFieldsName(MYSQL_RES *result, unsigned int numberFields, unsigned int **listMysqlType);
char ***mallocStringTable(unsigned int numberRows,unsigned int numberFields);
void freeResultStringTable(char* ***stringTable, unsigned int numberFields, unsigned int numberRows);
void freeFieldsList(char* **fieldsList, unsigned int numberFields);

MYSQL_STMT *stmtInitialisation(App *app);
unsigned int getTypeOfField(App *app, char *field, char *table);
void getProperFieldAndTable(char **field, char **table);

#endif // MYSQL_COMMON_FUNCTIONS
