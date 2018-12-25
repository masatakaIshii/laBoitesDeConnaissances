/*
** Filename : modelInit.c
**
** Made by  : Masataka ISHII
**
** Description  : init and load functions that uses API C MySQL
*/
#include <stdio.h>
#include "../../headers/model/modelInit.h"
#include "../../headers/model/modelCommon.h"

void dbConnect(App *app) {

    int check = 0;
    mysql_init(app->model.mysql);
    verifyPointer(app, app->model.mysql, "Problem with mysql_init");

    check = mysql_options(app->model.mysql, MYSQL_READ_DEFAULT_GROUP, "option");
    verifyMYSQLIntResult(app, check);

    if (!mysql_real_connect(app->model.mysql, "localhost", "root", "root", "the_box_of_knowledge", 0, NULL, 0)) {
        printf("%s", mysql_error(app->model.mysql));
        quitApp(app);
    }
}

void InitModel(Model *model) {

    model->listAllTables = NULL;

    model->tables = NULL;

    model->query.selectQuery.listColumnsRows = NULL;
    model->query.selectQuery.listFields = NULL;
    model->query.selectQuery.result = NULL;
    model->query.selectQuery.resultWithFieldsList = 0;

    model->query.stmtManager.buffersBind = NULL;
    model->query.stmtManager.params = NULL;
    model->query.stmtManager.stmt = NULL;
}

void initTables(MySqlTable *tables) {
    tables->listFieldsNames = NULL;
    tables->listFieldsTypes = NULL;
}

void loadFileModelTables(App *app) {

    /**
    *@todo : getTablesInformations
    *@todo : fill app->model.numberTables and app->model.tables
    *@todo : save array of structures in file modelTables
    */
}
/**

*@brief load the structure MySqlTable to get all metadatas for parameters
*
*@param (App *) app  - structure of app, the kernel of structure
*@param (Model *) model - structure of model to use mysql
*/

void loadTablesStruct(App *app, Model *model) {
    int i;
    unsigned int *listFieldsType;
    unsigned int numberFields = 0;

    model->tables = calloc(0, sizeof(MySqlTable) * model->numberAllTables);
    verifyPointer(app, model->tables, "Problem with memory allocation");

    for (i = 0; i < model->numberAllTables; i++) {
        strcpy(model->tables[i].tableName, model->listAllTables[i]);
        model->tables[i].listFieldsNames = getFieldsName(app, model->listAllTables[i], &numberFields, &listFieldsType);
        model->tables[i].listFieldsTypes = listFieldsType;
        model->tables[i].numberField = numberFields;
    }
}

/**
*@brief Initialisation of prepared query
*
*@param app : structure of application which content MYSQL variable
*@return preparedQuery : MYSQL_STMT
*/
MYSQL_STMT *stmtInitialisation(App *app) {
    MYSQL_STMT *mysqlStmt = mysql_stmt_init(app->model.mysql);
    verifyPointer(app, mysqlStmt, mysql_error(app->model.mysql));

    return mysqlStmt;
}

void loadStmtManager(App *app, MySqlStmtManager *stmtManager, int numberTables, int numberParams, const char *query) {

    int paramsCount;

    stmtManager->numberTables = numberTables;

    if (mysql_stmt_prepare(stmtManager->stmt, query, strlen(query))){

        printf("Error [MYSQL_STMT] in preparation of stmt : %s\n" , mysql_stmt_error(stmtManager->stmt));
        quitApp(app);
        exit(EXIT_FAILURE);
    }

    paramsCount = mysql_stmt_param_count(stmtManager->stmt);
    if (paramsCount != numberParams) {
        printf("Error [MYSQL_STMT] : the total parameters = %d, whereas numberParams = %d", paramsCount, numberParams);
        //quitStmtManager(stmtManager);
        quitApp(app);
        exit(EXIT_FAILURE);
    }
    stmtManager->numberParams = paramsCount;
}

