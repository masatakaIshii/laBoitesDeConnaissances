/*
** Filename : modelBindHelper.h
**
** Made by  : Masataka ISHII
**
** Description  : functions used API C MySQL for bind prepared queries
*/

#ifndef MYSQL_BINDHELPER_FUNCTIONS
#include "../struct.h"
#include "../common.h"

void setBindParams(App *app, char **paramsValues);

void loadBindParams(App *app, MySqlStmtManager *stmtManager, char **paramsValues);

void bindParamString(App *app, int index, MySqlStmtManager *stmtManager, char *paramValue);
void bindParamInt(App *app, int index, MySqlStmtManager *stmtManager, char *paramValue);
void bindParamDate(App *app, int index, MySqlStmtManager *stmtManager, char *paramValue);
void bindParamDouble(App *app, int index, MySqlStmtManager *stmtManager, char *paramValue);

int *getArrayLengthParams(App *app, MySqlTable *tables, int numberTables, char **paramsNames, int numberParams);

MYSQL_BIND *bindParams(App *app, MySqlTable *tables, int numberTables, char **paramsName, char **paramsValues,  int numberParams);
MYSQL_BIND bindOneParam(App *app, char *paramsName, char *paramsValues, MySqlTable *tables, int numberTables);

#endif // MYSQL_BINDHELPER_FUNCTIONS
