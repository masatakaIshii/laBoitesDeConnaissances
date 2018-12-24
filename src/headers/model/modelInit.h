/*
** Filename : modelInit.c
**
** Made by  : Masataka ISHII
**
** Description  : init and load functions that uses API C MySQL
*/

#ifndef MODEL_INIT_FUNCTIONS
#include "../common.h"

void dbConnect(App *app);
void InitModel(App *app);
void initStmtManager(MySqlStmtManager *stmtManager);
void loadFileModelTables(App *app);
void loadTablesStruct(App *app, Model *model);
MYSQL_STMT *stmtInitialisation(App *app);
void loadStmtManager(App *app, MySqlStmtManager *stmtManager, int numberTables, int numberParams, const char *query);
#endif // MODEL_INIT_FUNCTIONS
