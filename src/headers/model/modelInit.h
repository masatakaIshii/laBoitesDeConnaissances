/*
** Filename : modelInit.c
**
** Made by  : Masataka ISHII
**
** Description  : init and load functions that uses API C MySQL
*/

#ifndef MODEL_INIT_FUNCTIONS
#include "../struct.h"
#include "../common.h"
#include "modelCommon.h"

void dbConnect(App *app);
void InitModel(Model *model);

void initTables(MySqlTable *tables);
void getAllTablesNumberAndNames (App *app, Model *model);

void loadFileModelTables(App *app);
void loadTablesStructByQuery(App *app, Model *model);
void writeNumberAndNamesAndStructTablesInFile(App *app, Model *model);
void writeStructTables(App *app, Model *model, FILE *fp);
void readAndGetNumberAndNamesAndStructTables(App *app, Model *model);
void readAndGetStructTables(App *app, Model *model, FILE *fp);

void stmtInitialisation(App *app, MySqlStmtManager *stmtManager);
#endif // MODEL_INIT_FUNCTIONS
