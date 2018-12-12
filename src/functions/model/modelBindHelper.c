/*
** Filename : modelBindHelper.c
**
** Made by  : Masataka ISHII
**
** Description  : functions used API C MySQL for bind prepared queries
*/
#include "../../headers/model/modelBindHelper.h"
short numberOfQMarkAndParamsIsEqual(const char *query, int numberParams) {
    int numberQMark = 0;
    char temp[MAX];
    short result;
    char *target;

    strcpy(temp, query);
    while(strchr(temp, '?') != NULL) {
        target = strchr(temp, '?');
        if (target) {
            temp[target - temp] = '_';
            numberQMark++;
        }
    }

    result = (numberQMark == numberParams) ? 1 : 0;

    return result;
}

MYSQL_BIND *bindParams(App *app, char **tableNames, char **paramsName, char **paramsValues, int numberTables, int numberParams){
    MYSQL_BIND *params = malloc(sizeof(MYSQL_BIND) * numberParams);

    TableMysql *tables = loadTablesStruct(tableNames, numberTables);


    //load structure Table

    /*
    for
        get name
        get buffer_type(name, table->arrayField, table->arrayTypeField, table->numberField);
        get buffer(paramsValues[i], type);
        get buffer_length(paramsValues[i], type);
        is_null = 0;
        get length = if(type) ? strlen(buffer) : 0

    */

    return params;
}

/**
*load the array of structure TableMysql
*@param
*
*/
TableMysql *loadTablesStruct(char **listTables, int numberTables) {
    int i;
    TableMysql *loadTables;
    char **listFields;
    int **listFieldsType;

    loadTables = malloc(sizeof(TableMysql) * numberTables);
    for (i = 0; i < numberTables; i++) {
        loadTables[i].
    }
}
