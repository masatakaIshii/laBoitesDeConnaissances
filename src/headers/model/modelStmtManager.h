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

void setPreparedQuery(App *app, char *query, char **tablesNames, int numberTables, char **paramsNames, char **paramsValues);
void loadStmtManager(App *app,MySqlStmtManager * stmtManager, char **tablesNames, char **paramsNames);
void getParamsNames(App *app, MySqlStmtManager  *stmtManager, char *query, int numberParams);
void getBeginAndEndOfParamName(char *query, int *minIndex, int *maxIndex);
void mySubstring(Varchar newString, const char* stringToSub, int minIndex, int maxIndex);
void addStringInList(App *app, Varchar paramName, Varchar **listString, int *currentLength);
int getTypeField(char *paramName, MySqlTable *tables, Varchar *tablesNames, int numberTables);

#endif // MODEL_STMT_MANAGER

