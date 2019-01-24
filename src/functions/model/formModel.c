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
