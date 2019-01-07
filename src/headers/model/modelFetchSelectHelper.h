/*
** Filename : modelFetchSelectHelper.c
**
** Made by  : Masataka ISHII
**
** Description  : functions to fetch query and fill structure of SelectQuery
*/

#ifndef MODEL_FETCH_SELECT_HELPER
#include "../struct.h"
#include "modelCommon.h"

void fetchStmtToFillSelectQuery(App *app, MySqlStmtManager *stmtManager, SelectQuery *selectQuery);
char *getFetchValuesComparedToMysqlType(App *app, MySqlStmtManager *stmtManager, int indexColumn);
void copyNumberToString(App *app, char **stringToFill, char *format, int index, MySqlStmtManager *stmtManager);
void copyDateTimeToString(App *app, char **stringToFill, int index, MySqlStmtManager *stmtManager);
void copyStringAfterFetchLength(App *app, char **stringToFill, int index, MySqlStmtManager *stmtManager);

#endif // MODEL_FETCH_SELECT_HELPER

