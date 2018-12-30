/*
** Filename : modelInit.c
**
** Made by  : Masataka ISHII
**
** Description  : init and load functions that uses API C MySQL
*/

#include "../../headers/model/modelInit.h"

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
    app->model.ifMysqlIsInit = 1;
}

void InitModel(Model *model) {

    model->ifMysqlIsInit = 0;

    model->listAllTables = NULL;
    model->tables = NULL;
    model->numberAllTables = 0;

    model->query.selectQuery.listColumnsRows = NULL;
    model->query.selectQuery.listFields = NULL;
    model->query.selectQuery.result = NULL;
    model->query.selectQuery.resultWithFieldsList = 0;

    model->query.stmtManager.buffersBind = NULL;
    model->query.stmtManager.params = NULL;
    model->query.stmtManager.numberParams = 0;
    model->query.stmtManager.numberTables = 0;
    model->query.stmtManager.stmt = NULL;
    model->query.stmtManager.ifStmtIsInit = 0;
    model->query.stmtManager.tablesNames = NULL;
    model->query.stmtManager.paramsNames = NULL;
}

void initTables(MySqlTable *tables) {
    tables->listFieldsNames = NULL;
    tables->listFieldsTypes = NULL;
}

void loadFileModelTables(App *app) {

    int i, j;

    getAllTablesNumberAndNames(app, &app->model);

    loadTablesStructByQuery(app, &app->model);

    writeNumberAndNamesAndStructTablesInFile(app, &app->model);

    freeStructTableMysql(&app->model);

//    readAndGetNumberAndNamesAndStructTables(app, &app->model);

//    for (i = 0; i < app->model.numberAllTables; i++) {
//        printf("tables[%d].tablesName : %s\n", i, app->model.tables[i].tableName);
//        for (j = 0; j < app->model.tables[i].numberField; j++) {
//            printf("tables[%d].listFieldsName[%d] : %s\n", i, j, app->model.tables[i].listFieldsNames[j]);
//            printf("tables[%d].listFieldsType[%d] : %u\n", i, j, app->model.tables[i].listFieldsTypes[j]);
//        }
//        printf("\n");
//    }
}

/**
*@brief to get the number of all tables and their names and save in model's structure
*
*@param (App *) app - structure of app, the kernel
*@param (Model *) model - structure of all informations linked to database
*/
void getAllTablesNumberAndNames (App *app, Model *model) {
    MYSQL_ROW row;
    unsigned int numberTables;
    int i = 0;
    MYSQL_RES *resultTables = mysql_list_tables(model->mysql, NULL);
    verifyPointer(app, resultTables, mysql_error(model->mysql));

    numberTables = mysql_num_rows(resultTables);

    model->listAllTables = malloc(sizeof(Varchar) * numberTables);
    while((row = mysql_fetch_row(resultTables)) != NULL) {
        strcpy(model->listAllTables[i], row[0]);
        i++;
    }

    model->numberAllTables = (int)numberTables;

    mysql_free_result(resultTables);
}

/**
*@brief load the structure MySqlTable to get all metadatas for parameters
*
*@param (App *) app - structure of app that containt all necessary load and quit structure
*@param (Model *) model - structure of model to use mysql
*/

void loadTablesStructByQuery(App *app, Model *model) {
    int i;
    unsigned int *listFieldsType;
    unsigned int numberFields = 0;

    model->tables = malloc(sizeof(MySqlTable) * (model->numberAllTables));
    verifyPointer(app, model->tables, "Problem with memory allocation");

    for (i = 0; i < model->numberAllTables; i++) {
        strcpy(model->tables[i].tableName, model->listAllTables[i]);

        model->tables[i].listFieldsNames = getFieldsName(app, model->tables[i].tableName, &numberFields, &listFieldsType);

        model->tables[i].listFieldsTypes = listFieldsType;

        model->tables[i].numberField = numberFields;
    }

}

/**
*@brief to write number and names and structures of all tables in file numberNamesStructTables
*
*@param (App *) app - structure of app that containt all necessary load and quit structure
*@param (Model *) model - structure of model to use mysql
*/
void writeNumberAndNamesAndStructTablesInFile(App *app, Model *model) {
    FILE *fp;
    int result;

    fp = fopen("numberNamesStructTables", "wb");
    verifyPointer(app, fp, "Problem with open file numberNamesStructTables for write");

    result = fwrite(&model->numberAllTables, sizeof(int), 1, fp);

    verifyResultFile(app, result, 1, "Problem with fwrite &model->numberAllTables\n");

    result = fwrite(model->listAllTables, sizeof(Varchar), model->numberAllTables, fp);
    verifyResultFile(app, result, model->numberAllTables, "Problem with fwrite model->listAllTables\n");

    writeStructTables(app, model, fp);

    fclose(fp);
}

void writeStructTables(App *app, Model *model, FILE *fp) {
    int i;
    int result;

    for (i = 0; i < model->numberAllTables; i++) {
        result = fwrite(&model->tables[i].numberField, sizeof(int), 1, fp);
        verifyResultFile(app, result, 1, "Problem in fwrite for &model->tables[i].numberField");

        result = fwrite(&model->tables[i].tableName, sizeof(Varchar), 1, fp);
        verifyResultFile(app, result, 1, "Problem in fwrite for &model->tables[i].tableName");

        result = fwrite(model->tables[i].listFieldsTypes, sizeof(int), model->tables[i].numberField, fp);
        verifyResultFile(app, result, model->tables[i].numberField, "Problem in fwrite for model->tables[i].listFieldsTypes");

        result = fwrite(model->tables[i].listFieldsNames, sizeof(Varchar), model->tables[i].numberField, fp);
        verifyResultFile(app, result, model->tables[i].numberField, "Problem in fwrite formodel->tables[i].listFieldsNames");
    }

}
/**
*@brief readAndGetNumberAndNamesAndStructTables : function allowing to fill MysqlTableStruct
*
*@param (App *) app - structure that content all structures of application
*@param (Model *) model - structure that content all informations about database
*/
void readAndGetNumberAndNamesAndStructTables(App *app, Model *model){
    FILE *fp;
    int result;

    fp = fopen("numberNamesStructTables", "rb");

    verifyPointer(app, fp, "Problem with open file numberNamesStructTables for read");

    result = fread(&model->numberAllTables, sizeof(int), 1, fp);

    verifyResultFile(app, result, 1, "Problem with fread &model->numberAllTables\n");

    model->listAllTables = malloc(sizeof(Varchar) * model->numberAllTables);
    result = fread(model->listAllTables, sizeof(Varchar), model->numberAllTables, fp);
    verifyResultFile(app, result, model->numberAllTables, "Problme with fread model->listAllTables\n");

    readAndGetStructTables(app, model, fp);

    fclose(fp);
}

void readAndGetStructTables(App *app, Model *model, FILE *fp) {
    int i;
    int result;

    model->tables = malloc(sizeof(MySqlTable) * model->numberAllTables);
    for (i = 0; i < model->numberAllTables; i++) {
        result = fread(&model->tables[i].numberField, sizeof(int), 1, fp);
        verifyResultFile(app, result, 1, "Problem in fread for &model->tables[i].numberField\n");

        result = fread(&model->tables[i].tableName, sizeof(Varchar), 1, fp);
        verifyResultFile(app, result, 1, "Problem in fread for &model->tables[i].tableName\n");

        model->tables[i].listFieldsTypes = malloc(sizeof(int) * model->tables[i].numberField);
        result = fread(model->tables[i].listFieldsTypes, sizeof(int), model->tables[i].numberField, fp);
        verifyResultFile(app, result, model->tables[i].numberField, "Problem in fread for model->tables[i].listFieldsTypes\n");

        model->tables[i].listFieldsNames = malloc(sizeof(Varchar) * model->tables[i].numberField);
        result = fread(model->tables[i].listFieldsNames, sizeof(Varchar), model->tables[i].numberField, fp);
        verifyResultFile(app, result, model->tables[i].numberField, "Problem in fread for model->tables[i].listFieldsNames\n");
    }
}

/**
*@brief Initialization of prepared query
*
*@param app : structure of application which content MYSQL variable
*@return preparedQuery : MYSQL_STMT
*/
void stmtInitialisation(App *app, MySqlStmtManager *stmtManager) {

    stmtManager->stmt = mysql_stmt_init(app->model.mysql);
    verifyPointer(app, stmtManager->stmt, mysql_stmt_error(stmtManager->stmt));
    app->model.query.stmtManager.ifStmtIsInit = 1;
}



