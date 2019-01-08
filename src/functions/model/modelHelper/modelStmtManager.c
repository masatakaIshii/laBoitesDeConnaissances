/*
** Filename : modelStmtManager.c
**
** Made by  : Masataka ISHII
**
** Description  : set stmtManager's structure functions that uses API C MySQL
*/

#include "../../../headers/model/modelHelper/modelStmtManager.h"
/**
*@brief setPreparedQuery : for fill the structure stmtManager with the exception of *bufferBind
*
*@param (char **) tablesNames : list of tables names
*@param (int) numberTables : number of tables used for the prepared query
*@param (char **) paramsNames : list of parameters names used for the prepared query
*@param (int) numberTables : number of params that use for the prepared query
*@param (char **) paramsValues : list of parameters values used for the prepared query
*/
void setPreparedQuery(App *app, char *query, char **tablesNames, int numberTables){

    MySqlStmtManager *stmtManager = &app->model.query.stmtManager;

    stmtInitialisation(app, stmtManager);

    if (mysql_stmt_prepare(stmtManager->stmt, query, strlen(query))){

        printf("Error [MYSQL_STMT] in preparation of stmt : %s\n" , mysql_stmt_error(stmtManager->stmt));
        quitApp(app);
        exit(EXIT_FAILURE);
    }

    stmtManager->currentQuery = malloc(sizeof(char) * (strlen(query) + 1));
    strcpy(stmtManager->currentQuery, query);

    //load numberParams, numberTables, tables and params names in stmtManager
    loadStmtManager(app, stmtManager, tablesNames, numberTables);

        //load app->model.tables
    readAndGetNumberAndNamesAndStructTables(app, &app->model);

    getParamsNames(app, stmtManager, query, stmtManager->numberParams);

    loadStmtManagerBindTypes(app, &app->model);

    freeStructTableMysql(&app->model);
}

void loadStmtManager(App *app,MySqlStmtManager * stmtManager, char **tablesNames, int numberTables) {
    int i;

    stmtManager->numberParams = mysql_stmt_param_count(stmtManager->stmt);
    stmtManager->numberTables = numberTables;

    stmtManager->tablesNames = malloc(sizeof(Varchar) * stmtManager->numberTables);

    for (i = 0; i < stmtManager->numberTables; i++){
        strcpy(stmtManager->tablesNames[i], tablesNames[i]);
    }
}

/* thinking if loadStmtManagerBindTypes have to be in modelBindHelper.c or not */
void loadStmtManagerBindTypes(App *app, Model *model) {

    int i;
    MySqlStmtManager *stmtManager = &model->query.stmtManager;

    stmtManager->buffersBind = malloc(sizeof(MYSQL_BIND) * stmtManager->numberParams);
    memset(stmtManager->buffersBind, 0, sizeof(MYSQL_BIND));
    verifyPointer(app, stmtManager->buffersBind, "Problem malloc stmtManager->params in loadStmtManagerParams");

    for (i = 0; i < stmtManager->numberParams; i++) {
        stmtManager->buffersBind[i].buffer_type = getTypeField(stmtManager->paramsNames[i], model, stmtManager);
    }
}

int getTypeField(Varchar paramName, Model *model, MySqlStmtManager *stmtManager) {
    MySqlTable *tables = model->tables;
    Varchar table;
    Varchar checkSplitParamName;
    int typeField = -1;
    Varchar *tablesNames = stmtManager->tablesNames;
    int numberTables = model->numberAllTables;
    int i;
    int j;

    if (stmtManager->numberTables > 1) {
        strcpy(checkSplitParamName, paramName);
        getProperFieldAndTable(paramName, table);
        if (strncmp(checkSplitParamName, paramName, strlen(paramName)) == 0) {
            printf("Warning : in modelStmtManager.c, the paramName go to getProperFieldAndTable but still doesn't change : %s\n", paramName);
        }

    } else {
        strcpy(table, tablesNames[0]);
    }

    for (i = 0; i < numberTables; i++) {
        if (strncmp(table, tables[i].tableName, strlen(table) + 1) == 0) {
            for (j = 0; j < tables[i].numberField; j++) {

                if (strncmp(paramName, tables[i].listFieldsNames[j], strlen(paramName) + 1) == 0) {
                    typeField = tables[i].listFieldsTypes[j];
                }
            }
        }
    }

    return typeField;
}

/**
*@brief if field is juncture, separated "table.field" to "table" and "field"
*
*@param field : address of field
*@param table : address of table
*/
void getProperFieldAndTable(Varchar field, Varchar table) {
    char temp[255];

    //Check if field is juncture
    if (strchr(field, '.')) {
        strcpy(temp, field);
        sprintf(field, "%s", strchr(temp, '.') + 1);

        //verify if table content a value, if table is NULL it'll be affected
        strcpy(table, temp);
        table[strchr(temp, '.') - temp] = '\0';

    }
}
