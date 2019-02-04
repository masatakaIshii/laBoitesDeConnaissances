/*
** Filename : formModel.h
**
** Made by  : Masataka ISHII
**
** Description  : function concern to form and query
*/

#ifndef FORM_MODEL
#include "../struct.h"
#include "modelHelper/modelInit.h"
#include "modelHelper/modelStmtManager.h"
#include "modelHelper/modelBindHelper.h"
#include "modelHelper/modelIUD.h"

MySqlTable getTable(App *app, char *tableName);

MySqlTable copyStructTable(App *app, MySqlTable table);

int sendInsertQuery(App *app, QueryForm *qForm);
char** getTablesValues(App *app, Varchar tableName);;
char **getInsertValues(App *app, Varchar *values, int numberFields);
void freeArrayString(char **strings, int numberFields);

#endif // FORM_MODEL

