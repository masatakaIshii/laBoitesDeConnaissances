/*
** Filename : modelStmtManager.c
**
** Made by  : Masataka ISHII
**
** Description  : set stmtManager's structure functions that uses API C MySQL
*/
#ifndef MODEL_STMT_MANAGER
#include "../struct.h"
#include "../common.h"
#include "modelCommon.h"
#include "modelInit.h"

void setPreparedQuery(App *app, char *query, char **tablesNames, int numberTables);
void loadStmtManager(App *app,MySqlStmtManager * stmtManager, char **tablesNames, int numberTables);
void getParamsNames(App *app, MySqlStmtManager  *stmtManager, char *query, int numberParams);
void getBeginAndEndOfParamName(char *query, int *minIndex, int *maxIndex);
void mySubstring(Varchar newString, const char* stringToSub, int minIndex, int maxIndex);
void addStringInList(App *app, Varchar paramName, Varchar **listString, int *currentLength);

void loadStmtManagerBindTypes(App *app, Model *model);
int getTypeField(Varchar paramName, Model *model, MySqlStmtManager *stmtManager);
void getProperFieldAndTable(Varchar field, Varchar table);

void fillParams(App *app, int paramType, MySqlParamsBind *params, char *paramValue);
void fillParamsString(App *app, MySqlParamsBind *params, char *paramValue);
void fillParamInt(App *app, MySqlParamsBind *params, char *paramValue);
void fillParamDouble(App *app, MySqlParamsBind *params, char *paramValue);
#endif // MODEL_STMT_MANAGER

