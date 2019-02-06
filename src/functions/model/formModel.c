/*
** Filename : formModel.c
**
** Made by  : Masataka ISHII
**
** Description  : function concern to form and query
*/
#include "../../headers/model/formModel.h"

MySqlTable getTable(App *app, char *tableName) {

    int i;
    Model *model = &app->model;
    MySqlTable table;

    readAndGetNumberAndNamesAndStructTables(app, model);

    for (i = 0; i < model->numberAllTables; i++) {
        if (strncmp(model->listAllTables[i], tableName, strlen(tableName) + 1) == 0) {
            table = copyStructTable(app, model->tables[i]);
        }
    }

    freeStructTableMysql(model);

    return table;
}

MySqlTable copyStructTable(App *app, MySqlTable table) {
    MySqlTable newTable;
    int i;

    strcpy(newTable.tableName, table.tableName);
    newTable.numberField = table.numberField;

    newTable.listFieldsNames = malloc(sizeof(Varchar) * newTable.numberField);
    verifyPointer(app, newTable.listFieldsNames, "Problem malloc listFieldsNames in copyStructTable\n");

    newTable.listFieldsTypes = malloc(sizeof(int) * newTable.numberField);
    verifyPointer(app, newTable.listFieldsTypes, "Problem malloc listFieldsTypes in copyStructTable\n");

    for (i = 0; i < table.numberField; i++) {
        strcpy(newTable.listFieldsNames[i], table.listFieldsNames[i]);
        newTable.listFieldsTypes = table.listFieldsTypes;
    }

    return newTable;
}

int sendInsertQuery(App *app, QueryForm *qForm){

    int result = 0;
    char **tables = NULL;
    char **values = NULL;

    tables = getTablesValues(app, qForm->tableName);
    values = getInsertValues(app, qForm->values, qForm->numberFields);

    int i;
    for (i = 0; i < qForm->numberFields; i++){
        printf("qForm->fields[%d] : %s\n", i, qForm->fields[i]);
        printf("values[%d] : %s\n", i, values[i]);
    }


    setPreparedQuery(app, qForm->query, tables, 1);
    setBindParams(app, values, qForm->query);
    result = sendPreparedQueryIUD(app, qForm->query);

    quitStmtManager(&app->model.query.stmtManager);
    freeArrayString(tables, 1);
    freeArrayString(values, qForm->numberFields);

    return result;
}

char **getTablesValues(App *app, Varchar tableName){
    char **tables = malloc(sizeof(char*));

    tables[0] = malloc(sizeof(char) * (strlen(tableName) + 1));

    strcpy(tables[0], tableName);

    return tables;
}

char **getInsertValues(App *app, Varchar *valuesVarchar, int numberFields){
    int i;
    char **values = malloc(sizeof(char*) * numberFields);

    for (i = 0; i < numberFields; i++){
        values[i] = malloc(sizeof(char) * (strlen(valuesVarchar[i]) + 1));
        strcpy(values[i], valuesVarchar[i]);
        printf("values[%d] : %s\n", i, values[i]);
    }

    return values;
}

void freeArrayString(char **strings, int numberFields){
    int i;

    for (i = 0; i < numberFields; i++){
        free(strings[i]);
    }

    free(strings);
}
