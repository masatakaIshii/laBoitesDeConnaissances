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

int *getArrayTypeParams(App *app, MySqlTable *tables, int numberTables, char **paramsName, int numberParams);
void loadBindParams(App *app, MySqlStmtManager *stmtManager, char **paramsNames, char **paramsValues);

void bindParamString(int index, MySqlStmtManager *stmtManager, enum_field_types typeParam, char *paramValue);
void bindParamInt(int index, MySqlStmtManager *stmtManager, enum_field_types typeParam, char *paramValue);
void bindParamDate(int index, MySqlStmtManager *stmtManager, enum_field_types typeParam, char *paramValue);

int *getArrayLengthParams(App *app, MySqlTable *tables, int numberTables, char **paramsNames, int numberParams);

MYSQL_BIND *bindParams(App *app, MySqlTable *tables, int numberTables, char **paramsName, char **paramsValues,  int numberParams);
MYSQL_BIND bindOneParam(App *app, char *paramsName, char *paramsValues, MySqlTable *tables, int numberTables);
void getProperFieldAndTable(char **field, char **table);


#endif // MYSQL_BINDHELPER_FUNCTIONS
