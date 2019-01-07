/*
** Filename : modelSelect.c
**
** Made by  : Masataka ISHII
**
** Description  : select functions used API C MySQL for select data in database
*/
#ifndef MYSQL_SELECT_FUNCTIONS
#include "modelCommon.h"
#include "../struct.h"
#include "modelFetchSelectHelper.h"

void getSelectQuery (App *app, const char *currentQuery);
void getPreparedSelectQuery(App *app, const char *currentQuery);
void fetchFieldsSelectQueryPrepared(App *app, MySqlStmtManager *stmtManager, SelectQuery *selectQuery);
void executeBindInputAndGetResult(App *app, MySqlStmtManager *stmtManager, SelectQuery *selectQuery);

void fetchFieldsOfQuerySelect(App *app, SelectQuery *selectQuery, int **listFieldsTypes);
void bindSelectQueryPrepared(App *app, MySqlStmtManager *stmtManager, SelectQuery *selectQuery);

short checkIfQueryConcernMoreThan1Table(MYSQL_FIELD *fields, int numberFields);
void fetchQuerySelect(App *app, SelectQuery *selectQuery);
void fetchOneRowQuerySelect(App *app, SelectQuery *selectQuery, unsigned long *lengths, MYSQL_ROW row, int i);

void initBufferTypeAndPutFieldsTypes(App *app, MYSQL_BIND **bufferBind, unsigned int numberFields, int *listFieldsTypes);

void addFieldsToResult(App *app);
void removeFieldsInResult(App *app);

#endif
