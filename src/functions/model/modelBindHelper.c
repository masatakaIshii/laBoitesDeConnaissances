/*
** Filename : modelBindHelper.c
**
** Made by  : Masataka ISHII
**
** Description  : functions used API C MySQL for bind prepared queries
*/

#include "../../headers/model/modelBindHelper.h"

void loadBindParams(App *app, MySqlStmtManager *stmtManager, char **paramsNames, char **paramsValues){
    int i;
    enum_field_types typeParam;

    stmtManager->buffersBind = malloc(sizeof(MYSQL_BIND) * stmtManager->numberParams);
    verifyPointer(app, stmtManager->buffersBind, "problem with memory allocation in stmtManager->bufferBind");

    for (i = 0; i < stmtManager->numberParams; i++) {
//        typeParam = (enum_field_types)getTypeField(paramsNames[i], stmtManager->tables, stmtManager->numberTables);
//
//        if (typeParam == MYSQL_TYPE_BLOB || typeParam == MYSQL_TYPE_STRING || typeParam == MYSQL_TYPE_VAR_STRING){
//
//            bindParamString(i, stmtManager, typeParam, paramsValues[i]);
//        }
//
//        if (typeParam == MYSQL_TYPE_LONG || typeParam == MYSQL_TYPE_SHORT || typeParam == MYSQL_TYPE_TINY) {
//            bindParamInt(i, stmtManager, typeParam, paramsValues[i]);
//        }
//
//        if (typeParam == MYSQL_TYPE_DATE || typeParam == MYSQL_TYPE_DATETIME || typeParam == MYSQL_TYPE_TIMESTAMP) {
//            //binParamDate(i, stmtManager, typeParam, paramsValues[i]);
//        }
//
//        if (typeParam == MYSQL_TYPE_DOUBLE) {
//            //TODO bindParamDouble
//        }
    }
}

int getTypeField(char *paramName, MySqlTable *tables, int numberTables) {
    char *table;
    int typeField = -1;
    int i;
    int j;

    if (numberTables > 1) {
        getProperFieldAndTable(&paramName, &table);
    } else {
        table = tables[0].tableName;
    }

    for (i = 0; i < numberTables; i++) {
        for (j = 0; j < tables[i].numberField; j++) {
            if (table == tables[i].tableName) {
                if (strncmp(paramName, tables[i].listFieldsNames[j], strlen(paramName) + 1) == 0) {
                    printf("le type %s de paramName est de :%d\n", paramName, tables[i].listFieldsTypes[j]);
                    typeField = tables[i].listFieldsTypes[j];
                }
            }
        }
        printf("\n");
    }

    return typeField;
}

void bindParamString(int index, MySqlStmtManager *stmtManager, enum_field_types typeParam, char *paramValue) {
    unsigned long length = strlen(paramValue);
    int isNull = (strcmp(paramValue, "") == 0) ? 0 : 1;

    stmtManager->buffersBind[index].buffer_type = typeParam;
    stmtManager->buffersBind[index].buffer_length = length + 1;
    stmtManager->buffersBind[index].buffer = (void *)paramValue;
    stmtManager->buffersBind[index].is_null = (my_bool *)&isNull;
    stmtManager->buffersBind[index].length = &length;
}

void bindParamInt(int index, MySqlStmtManager *stmtManager, enum_field_types typeParam, char *paramValue) {
    int value = atoi(paramValue);
    int isNull = (strcmp(paramValue, "") == 0) ? 0 : 1;

    stmtManager->buffersBind[index].buffer_type = typeParam;
    stmtManager->buffersBind[index].buffer = (void *)&value;
    stmtManager->buffersBind[index].is_null = (my_bool *)&isNull;
    stmtManager->buffersBind[index].length = 0;
}

void bindParamDate(int index, MySqlStmtManager *stmtManager, enum_field_types typeParam, char *paramValue) {

}


//
//int *getArrayTypeParams(App *app, MySqlTable *tables, int numberTables, char **paramsName, int numberParams) {
//    int typeField;
//    int i;
//    int *arrayTypesParams = calloc(numberParams, sizeof(int*));
//    verifyPointer(app, arrayTypesParams, "Problem malloc arrayTypesParams");
//
//    for (i = 0; i < numberParams; i++) {
//        typeField = getTypeField(paramsName[i], tables, numberTables);
//        if (typeField == -1) {
//            verifyPointer(app, NULL, "Problem with typeField");
//        }
//        arrayTypesParams[i] = typeField;
//    }
//
//    return arrayTypesParams;
//}

//
///**
//*@brief bind parameters values and metadatas for the prepared query
//*
//*@param (App *) app  - structure of app to use mysql
//*@param (char **) tableNames - names of tables concern to the query
//*@param (char **) paramsName - names of fields concern to the params
//*@param (char **) paramsValues - values of params to bind
//*@param (int) numberParams - number of params
//*@return (MYSQL_BIND *) params - all params completed
//*/
//MYSQL_BIND *bindParams(App *app, MySqlTable *tables, int numberTables, char **paramsName, char **paramsValues,  int numberParams){
//
//    int i;
//
//    unsigned int typeParam;
//
//    MYSQL_BIND *params = malloc(sizeof(MYSQL_BIND) * numberParams);
//    memset(params, 0, numberParams);
//
//    for (i = 0; i < numberParams; i++) {
//        params[i] = bindOneParam(app, paramsName[i], paramsValues[i], tables, numberTables);
//    }
//
//    /*TODO :
//        -obtenir tableau de length des params, si c'est des num => 0;
//        -adapter bindParams pour mettre en paramètre MySqlTable
//    */
//
//    /*
//    for
//        get name
//        get buffer_type(name, table->arrayField, table->arrayTypeField, table->numberField);
//        get buffer(paramsValues[i], type);
//        get buffer_length(paramsValues[i], type);
//        is_null = 0;
//        get length = if(type) ? strlen(buffer) : 0
//
//    */
//
//    return params;
//}
//
//
//MYSQL_BIND bindOneParam(App *app, char *paramsName, char *paramsValues, MySqlTable *tables, int numberTables) {
//
//    MYSQL_BIND param;
//    char table[255];
//    char field[255];
//
//    strcpy(field, paramsName);
//    printf("%s\n", field);
//
//    //param.buffer_type = getTypeOfField();
//
//    /*
//    for
//    */
//
//    return param;
//}

/**
*@brief if field is juncture, separated "table.field" to "table" and "field"
*
*@param field : address of field
*@param table : address of table
*/
void getProperFieldAndTable(char **field, char **table) {
    char temp[255];

    //Check if field is juncture
    if (strchr(*field, '.')) {
        strcpy(temp, *field);
        sprintf(*field, "%s", strchr(temp, '.') + 1);

        //verify if table content a value, if table is NULL it'll be affected
        if (table && (*table) == NULL) {
            *table = malloc(sizeof(char) * (strlen(temp) + 1));
            *table = temp;
            (*table)[strchr(temp, '.') - temp] = '\0';
        }
    }
}

