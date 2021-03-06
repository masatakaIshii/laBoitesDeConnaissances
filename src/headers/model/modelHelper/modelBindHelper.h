/*
** Filename : modelBindHelper.h
**
** Made by  : Masataka ISHII
**
** Description  : functions used API C MySQL for bind prepared queries
*/

#ifndef MYSQL_BINDHELPER_FUNCTIONS

#include "../../struct.h"
#include "../../common.h"
#include "modelInit.h"
#include "modelQuit.h"
#include "modelCommon.h"
#include "modelParamFinder.h"

void setBindParams(App *app, char **paramsValues, char *query);

void bindSelectQueryPrepared(App *app, MySqlStmtManager *stmtManager, SelectQuery *selectQuery);
int getTypeField(Varchar paramName, Model *model, MySqlStmtManager *stmtManager);
void getProperFieldAndTable(Varchar field, Varchar table);

void loadBindParams(App *app, MySqlStmtManager *stmtManager, BindType bindIO, char **paramsValues);
void loadStmtManagerBindTypes(App *app, Model *model);

void preparedBindParamString(App *app, int index, MySqlStmtManager *stmtManager, char *paramValue, BindType bindIO);
void preparedBindParamInt(App *app, int index, MySqlStmtManager *stmtManager, char *paramValue, BindType bindIO);
void preparedBindParamDate(App *app, int index, MySqlStmtManager *stmtManager, char *paramValue, BindType bindIO);
void preparedBindParamDouble(App *app, int index, MySqlStmtManager *stmtManager, char *paramValue, BindType bindIO);

void bindParamString(int index, MySqlStmtManager *stmtManager, BindType bindIO);
void bindParamInt(int index, MySqlStmtManager *stmtManager, BindType bindIO);
void bindParamDate(int index, MySqlStmtManager *stmtManager, BindType bindIO);
void bindParamDouble(int index, MySqlStmtManager *stmtManager, BindType bindIO);

int *getArrayLengthParams(App *app, MySqlTable *tables, int numberTables, char **paramsNames, int numberParams);

MYSQL_BIND *bindParams(App *app, MySqlTable *tables, int numberTables, char **paramsName, char **paramsValues,  int numberParams);
MYSQL_BIND bindOneParam(App *app, char *paramsName, char *paramsValues, MySqlTable *tables, int numberTables);

#endif // MYSQL_BINDHELPER_FUNCTIONS
