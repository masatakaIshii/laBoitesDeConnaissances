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

MySqlTable getTable(App *app, char *tableName);

MySqlTable copyStructTable(App *app, MySqlTable table);

#endif // FORM_MODEL

