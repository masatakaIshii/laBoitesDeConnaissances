/*
** Filename : mysqlCommon.h
**
** Made by  : Masataka ISHII
**
** Description  : common functions used API C MySQL
*/

#ifndef MYSQL_COMMON_FUNCTIONS
#include <windows.h>
#include <winsock2.h>
#include <mysql.h>

void dbConnect(MYSQL* mysql);
void checkMYSQLError(void *functionResult, MYSQL* mysql);
char **getFieldsNameType(MYSQL* mysql, const char *table, unsigned int* numberFields);
char **fetchFieldsNameType(MYSQL_RES *result, unsigned int numberFields);
char ***mallocStringTable(unsigned int numberRows,unsigned int numberFields);
void freeResultStringTable(char* ***stringTable, unsigned int numberFields, unsigned int numberRows);
void freeFieldsList(char* **fieldsList, unsigned int numberFields);
#endif // MYSQL_COMMON_FUNCTIONS
