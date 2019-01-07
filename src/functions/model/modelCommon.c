/*
** Filename : modelCommon.c
**
** Made by  : Masataka ISHII
**
** Description  : common functions used API C MySQL
*/
#include "../../headers/model/modelCommon.h"
#include "../../headers/struct.h"

void verifyMYSQLIntResult(App *app, int result) {
    if (result != 0) {
        printf("%s", mysql_error(app->model.mysql));
        quitApp(app);
        exit(EXIT_FAILURE);
    }
}

void verifyPointerForQueryStmt(App *app, MySqlStmtManager *stmtManager, void *pointer, const char *message) {
    if (pointer == NULL) {
        printf("%s", message);
        quitApp(app);
        exit(EXIT_FAILURE);
    }
}

void verifyResultFile(App *app, int result, int nmemb, const char *message) {
    if (result != nmemb){
        printf("%s", message);
        quitApp(app);
        exit(EXIT_FAILURE);
    }
}

/**
*@brief To get array of fields name, possible to get unsigned int listMysqlType
*
*@param app : structure that content MYSQL's variable to get list
*@param table : name of table for get its fields
*@param numberFields : number fields of table
*@return fieldsName
*/
Varchar *getFieldsName(App *app, Varchar table, unsigned int* numberFields, unsigned int **listMysqlType) {
    Varchar *fieldsName;
    MYSQL_RES *resultFields;
    unsigned int fieldsCount;

    //result of table if is correct
    resultFields = mysql_list_fields(app->model.mysql, table, NULL);
    verifyPointer(app, resultFields, mysql_error(app->model.mysql));

    fieldsCount = mysql_num_fields(resultFields);

    // if address of numberFields is call in function, get number of fields
    *numberFields = fieldsCount;

    fieldsName = fetchFieldsName(app, resultFields, fieldsCount, listMysqlType);

    return fieldsName;
}

/**
*@brief Fetch values of query and copy to list of field, can fetch also int list of field type
*
*@param result : result of query
*@param numberFields : number of field of the list
*@param listMysqlType : int list that content type of field
*@return fieldsName
*/
Varchar *fetchFieldsName(App *app, MYSQL_RES *result, unsigned int numberFields, unsigned int **listMysqlType){
    Varchar *fieldsName;
    MYSQL_FIELD *fetchField;
    int i;

    fieldsName = malloc(sizeof(Varchar) * numberFields);
    verifyPointer(app, fieldsName, "Problem memory allocation for fieldsName");

    //check if listMysql address is call in parameter
    if (listMysqlType != NULL) {
        *listMysqlType = malloc(sizeof(unsigned int) * numberFields);
        verifyPointer(app, listMysqlType, "problem memory allocation for listMysqlType");
    }

    //fetch value and copy to list, possible to fetch also type in listMysqlType
    for (i = 0; i < numberFields; i++) {
        fetchField = mysql_fetch_field_direct(result, i);

        if (listMysqlType != NULL) {
            (*listMysqlType)[i] = (unsigned int)fetchField->type;
        }
        strcpy(fieldsName[i], fetchField->name);
    }

    return fieldsName;
}

/**
*@brief Malloc of table content rows and fields
*
*@param numberRows : number rows that to content table
*@param numberFields : number fields that to content table
*@return stringTable
*/
char ***mallocStringTable(unsigned int numberRows,unsigned int numberFields) {
    char *** stringTable;
    int i;

    stringTable = calloc(0, sizeof(char**) * numberRows);
    if (stringTable == NULL) {
        printf("Memory allocation problem for stringTable");
        exit(1);
    }
    for (i = 0; i < numberRows; i++) {
        *(stringTable + i) = calloc(0, sizeof(char*) * numberFields);
        if (*(stringTable + i) == NULL) {
            printf("Memory allocation problem for *(stringTable + i)");
            exit(1);
        }
    }

    return stringTable;
}
