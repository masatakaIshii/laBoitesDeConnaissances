/*
** Filename : mysqlCommon.c
**
** Made by  : Masataka ISHII
**
** Description  : common functions used API C MySQL
*/
#include <stdio.h>
#include "../../headers/common.h"
#include "../../headers/model/modelCommon.h"
#include "../../headers/model/modelQuit.h"

void dbConnect(App *app) {

    mysql_init(app->model.mysql);

    mysql_options(app->model.mysql, MYSQL_READ_DEFAULT_GROUP, "option");

    if (!mysql_real_connect(app->model.mysql, "localhost", "root", "root", "the_box_of_knowledge", 0, NULL, 0)) {
        printf("%s", mysql_error(app->model.mysql));
        mysql_close(app->model.mysql);
    }
}

void closeMySQL(App *app) {
    mysql_close(app->model.mysql);

    printf("closing suiccess");
}


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
        //quitStmtManager(stmtManager);
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
char **getFieldsName(App *app, const char *table, unsigned int* numberFields, unsigned int **listMysqlType) {
    char **fieldsName;
    MYSQL_RES *resultFields;
    unsigned int fieldsCount;

    //result of table if is correct
    resultFields = mysql_list_fields(app->model.mysql, table, NULL);
    verifyPointer(app, resultFields, (char *)mysql_error(app->model.mysql));

    fieldsCount = mysql_num_fields(resultFields);

    // if address of numberFields is call in function, get number of fields
    if (numberFields != NULL) {
        *numberFields = fieldsCount;
    }

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
char **fetchFieldsName(App *app, MYSQL_RES *result, unsigned int numberFields, unsigned int **listMysqlType){
    char **fieldsName;
    MYSQL_FIELD *fetchField;
    int i;

    fieldsName = malloc(sizeof(char*) * numberFields);
    verifyPointer(app, fieldsName, "Problem memory allocation for fieldsName");

    //check if listMysql address is call in parameter
    if (listMysqlType != NULL) {
        *listMysqlType = malloc(sizeof(unsigned int) * numberFields);
        verifyPointer(app, listMysqlType, "problem memory allocation for listMysqlType");
    }

    //fetch value and copy to list, possible to fetch also type in listMysqlType
    for (i = 0; i < numberFields; i++) {
        fetchField = mysql_fetch_field_direct(result, i);
        fieldsName[i] = malloc(sizeof(char) * (fetchField->name_length + 1));
        verifyPointer(app, fieldsName[i], "problem memory allocation for fieldsName[i]");
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

    stringTable = malloc(sizeof(char**) * numberRows);
    if (stringTable == NULL) {
        printf("Memory allocation problem for stringTable");
        exit(1);
    }
    for (i = 0; i < numberRows; i++) {
        *(stringTable + i) = malloc(sizeof(char*) * numberFields);
        if (*(stringTable + i) == NULL) {
            printf("Memory allocation problem for *(stringTable + i)");
            exit(1);
        }
    }

    return stringTable;
}

/**
*@brief Initialisation of prepared query
*
*@param app : structure of application which content MYSQL variable
*@return preparedQuery : MYSQL_STMT
*/
MYSQL_STMT *stmtInitialisation(App *app) {
    MYSQL_STMT *preparedQuery = mysql_stmt_init(app->model.mysql);
    verifyPointer(app, preparedQuery, mysql_error(app->model.mysql));

    return preparedQuery;
}

void initStmtManager(MySqlStmtManager *stmtManager) {

    stmtManager->params = NULL;
    stmtManager->params->paramsBuffer = NULL;
    stmtManager->params->paramsBufferLengths = NULL;
    stmtManager->params->paramsIsNull = NULL;
    stmtManager->params->paramsLengths = NULL;
    stmtManager->params->paramsTypes = NULL;
    stmtManager->params->datetimeBind = NULL;
    stmtManager->params->paramsDateTime = NULL;

    stmtManager->buffersBind = NULL;
    stmtManager->buffersBind->is_null = NULL;
    stmtManager->buffersBind->length = NULL;

    stmtManager->numberParams = 0;
    stmtManager->numberTables = 0;
}

void loadStmtManager(App *app, MySqlStmtManager *stmtManager, int numberTables, int numberParams, const char *query) {

    int paramsCount;

    stmtManager->stmt = stmtInitialisation(app);

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
