/*
** Filename : modelSelect.c
**
** Made by  : Masataka ISHII
**
** Description  : select functions used API C MySQL for select data in database
*/
#include "../../../headers/model/modelHelper/modelSelect.h"
/* --Select Query-- */
/**
*@brief To connect to the database and get result of select query
*
*@param (App *) app - structure of app to use mysql
*@param (const char *) currentQuery - the query for the database
*@param (unsigned int*) numberFields - pointer of number of fields
*@param (unsigned ind*) numberRows - pointer of number of rows
*@return (char ***) resultQuery - columns and rows of selection of query
*/
SelectQuery getSelectQuery (App *app, const char *currentQuery) {

    SelectQuery newSelectQuery;
    SelectQuery *selectQuery = &app->model.query.selectQuery;
    int checkResult = 0; // check if mysql_query is success => 0, or fail => =!0

    checkResult = mysql_query(app->model.mysql, currentQuery);
    verifyMYSQLIntResult(app, checkResult);

    selectQuery->listColumnsRows = NULL;
    selectQuery->listFields = NULL;

    selectQuery->result = mysql_store_result(app->model.mysql);
    selectQuery->mysqlResultBool = 1;
    verifyPointer(app, selectQuery->result, mysql_error(app->model.mysql));

    //get number of fields and row in result of query
    selectQuery->numberFields = mysql_num_fields(selectQuery->result);
    selectQuery->numberRows = mysql_num_rows(selectQuery->result);

    fetchFieldsOfQuerySelect(app, selectQuery, NULL);

    fetchQuerySelect(app, selectQuery);

    mysql_free_result(selectQuery->result);
    selectQuery->mysqlResultBool = 1;
    newSelectQuery = copySelectQuery(app, selectQuery);

    quitSelectQuery(selectQuery);
    return newSelectQuery;
}

void fetchFieldsOfQuerySelect(App *app, SelectQuery *selectQuery, int **listFieldsTypes) {

    int i;
    short moreThanOneTable = 0;
    char temp[100];
    MYSQL_FIELD *fields = mysql_fetch_fields(selectQuery->result);

    selectQuery->listFields = malloc(sizeof(Varchar) * selectQuery->numberFields);
    if (listFieldsTypes != NULL) {
        (*listFieldsTypes) = malloc(sizeof(int) * selectQuery->numberFields);
    }

    verifyPointer(app, selectQuery->listFields, "Problem memory allocation at selectQuery->listFields");

    moreThanOneTable = checkIfQueryConcernMoreThan1Table(fields, selectQuery->numberFields);

    for (i = 0; i < selectQuery->numberFields; i++) {

        if (moreThanOneTable) {
            strcpy(temp, fields[i].table);
            strcat(temp, ".");
            //selectQuery->listFields[i] = malloc(sizeof(char) * (strlen(fields[i].name) + strlen(fields[i].name) + 1));
            strcpy(selectQuery->listFields[i], strcat(temp, fields[i].name));

        } else {
            //selectQuery->listFields[i] = malloc(sizeof(char) * (strlen(fields[i].name) + 1));
            strcpy(selectQuery->listFields[i], fields[i].name);
        }
        if (listFieldsTypes != NULL) {
            (*listFieldsTypes)[i] = fields[i].type;
        }
    }
}
/**
*@brief Check if all fields have "table.field" form
*
*@param (MYSQL_FIELD *)fields - all fields infos of result of select query
*@param (int) numberFields - number fields of the result of select query
*/
short checkIfQueryConcernMoreThan1Table(MYSQL_FIELD *fields, int numberFields) {
    int i;
    char table[100];
    short result = 0;

    strcpy(table, fields[0].table);

    for (i = 1; i < numberFields && result == 0; i++) {
        if (strcmp(table, fields[i].table) != 0) {
            result = 1;
        }
    }

    return result;
}

/**
*@brief Fetch the query's results in table of rows and fields
*
*@param (unsigned int*) numberFields - pointer of number of fields
*@param (unsigned ind*) numberRows - pointer of number of rows
*@return (char ***) resultFetch - columns and rows of selection of query
*/
void fetchQuerySelect(App *app, SelectQuery *selectQuery) {

    MYSQL_ROW row; // fetch result of each row
    unsigned long *lengths; //array of lengths of each fetch result of row
    int i = 0;

    //malloc rows
    selectQuery->listColumnsRows = malloc(sizeof(char**) * selectQuery->numberRows);

    verifyPointer(app, selectQuery->listColumnsRows, "problem of allocation memory selectQuery->listColumnsRows\n");
    while((row = mysql_fetch_row(selectQuery->result))){

        if (row == NULL && strcmp(mysql_error(app->model.mysql), "") != 0){
            verifyPointer(app, row, strcat("Error[MySQL] : ", mysql_error(app->model.mysql)));
        }

        //get length of each value
        lengths = mysql_fetch_lengths(selectQuery->result);

        fetchOneRowQuerySelect(app, selectQuery, lengths, row, i);

        i++;
    }
}

void fetchOneRowQuerySelect(App *app, SelectQuery *selectQuery, unsigned long *lengths, MYSQL_ROW row, int i) {
    int j;
    int numberFields = selectQuery->numberFields;

    selectQuery->listColumnsRows[i] = malloc(sizeof(char*) * numberFields);
    verifyPointer(app, selectQuery->listColumnsRows[i], "Problem allocation memory selectQuery->listColumnsRows[i]");

    for (j = 0; j < numberFields; j++) {

        selectQuery->listColumnsRows[i][j] = malloc(sizeof(char) * (lengths[j] + 1));
        verifyPointer(app, selectQuery->listColumnsRows[i][j], "problem of allocation memory selectQuery->listColumnsRows[i][j]");
        sprintf(selectQuery->listColumnsRows[i][j],(row[j] != NULL)?row[j]:"");
    }
}


/* --Prepared Select Query-- */

SelectQuery getPreparedSelectQuery(App *app, const char *currentQuery) {

    SelectQuery *selectQuery = &app->model.query.selectQuery;
    MySqlStmtManager *stmtManager = &app->model.query.stmtManager;
    SelectQuery newSelectQuery;
    executeBindInputAndGetResult(app, stmtManager, selectQuery);


    if (stmtManager->params != NULL) {
        quitStmtParams(stmtManager);
    } else {
        printf("Error : the prepared query have to bind the parameter before to get result.\n");
        quitApp(app);
        exit(EXIT_FAILURE);
    }

    fetchFieldsSelectQueryPrepared(app, stmtManager, selectQuery);

    bindSelectQueryPrepared(app, stmtManager, selectQuery);

    fetchStmtToFillSelectQuery(app, stmtManager, selectQuery);

    newSelectQuery = copySelectQuery(app, selectQuery);

    mysql_stmt_free_result(stmtManager->stmt);
    selectQuery->mysqlResultBool = 0;

    quitSelectQuery(selectQuery);

    return newSelectQuery;
}

void executeBindInputAndGetResult(App *app, MySqlStmtManager *stmtManager, SelectQuery *selectQuery) {
    int check = 0;

    check = mysql_stmt_execute(stmtManager->stmt);
    verifyMYSQLIntResult(app, check);

    selectQuery->result = mysql_stmt_result_metadata(stmtManager->stmt);
    selectQuery->resultWithFieldsList=1;
    verifyPointer(app, selectQuery->result, mysql_stmt_error(stmtManager->stmt));

}

void fetchFieldsSelectQueryPrepared(App *app, MySqlStmtManager *stmtManager, SelectQuery *selectQuery) {
    int *listFieldsTypes;

    selectQuery->numberFields = mysql_stmt_field_count(stmtManager->stmt);

    selectQuery->numberRows = mysql_stmt_num_rows(stmtManager->stmt);

    fetchFieldsOfQuerySelect(app, selectQuery, &listFieldsTypes);

    initBufferTypeAndPutFieldsTypes(app, &stmtManager->buffersBind, selectQuery->numberFields, listFieldsTypes);

    free(listFieldsTypes);
}

void initBufferTypeAndPutFieldsTypes(App *app, MYSQL_BIND **bufferBind, unsigned int numberFields, int *listFieldsTypes) {
    int i;

    (*bufferBind) = malloc(sizeof(MYSQL_BIND) * numberFields);
    verifyPointer(app, (*bufferBind), "Problem malloc (*bufferBind) in initBufferTypeAndPutFieldsTypes\n");

    memset(*bufferBind, 0, sizeof(*bufferBind[0]));
    for (i = 0; i < numberFields; i++) {
        (*bufferBind)[i].buffer_type = listFieldsTypes[i];
    }
}

void addFieldsToSelectQuery(App *app, SelectQuery *selectQuery) {

    char ***inter;
    int i;
    //printf("\nin addFieldsToResult\n");

    if (selectQuery->resultWithFieldsList == 1) {
        printf("Warning : you already have fields list in your result. ");
        printf("The function addFieldsToResult is call few times.\n");
        return;
    }

    inter = malloc(sizeof(char**) * (++selectQuery->numberRows));
    verifyPointer(app, inter, "Problem malloc for inter in addFieldsToResult");

    for (i = 0; i < selectQuery->numberRows; i++) {
        if (i == 0) {
            inter[i] = copyListFields(app, selectQuery->listFields, selectQuery->numberFields);
        } else {
            inter[i] = copyListString(app, selectQuery->listColumnsRows[i - 1], selectQuery->numberFields);
        }
    }

    freeResultStringTable(&selectQuery->listColumnsRows, selectQuery->numberFields, selectQuery->numberRows - 1);
    selectQuery->listColumnsRows = inter;

    selectQuery->resultWithFieldsList = 1;
}

void removeFieldsToSelectQuery(App *app, SelectQuery *selectQuery) {
    char ***inter;
    int i;

    if (selectQuery->resultWithFieldsList == 0) {
        printf("Warning : you already don't have fields list in your result. ");
        printf("The function removeFieldsInResult have to be call if listColumnsRows have fields lists.\n");
        return;
    }

    inter = malloc(sizeof(char**) * (--selectQuery->numberRows));
    verifyPointer(app, inter, "Problem in inter in function removeFieldsInResult\n");

    for (i = 0; i < selectQuery->numberRows; i++) {
        inter[i] = copyListString(app, selectQuery->listColumnsRows[i + 1], selectQuery->numberFields);
    }

    freeResultStringTable(&selectQuery->listColumnsRows, selectQuery->numberFields, selectQuery->numberRows + 1);
    selectQuery->listColumnsRows = inter;

    selectQuery->resultWithFieldsList = 0;
}

SelectQuery copySelectQuery(App *app, SelectQuery *selectQuery) {

    SelectQuery newSelectQuery;

    newSelectQuery.listColumnsRows = copyListColumnsRows(app, selectQuery->listColumnsRows, selectQuery->numberRows, selectQuery->numberFields);
    newSelectQuery.listFields = copyVarcharListFields(app, selectQuery->listFields, selectQuery->numberFields);
    newSelectQuery.numberFields = selectQuery->numberFields;
    newSelectQuery.numberRows = selectQuery->numberRows;
    newSelectQuery.resultWithFieldsList = 0;
    newSelectQuery.mysqlResultBool = 0;

    return newSelectQuery;
}

char ***copyListColumnsRows(App *app, char ***list, unsigned int numberRows, unsigned int numberFields) {
    int i;
    int j;
    char ***newList;

    newList = malloc(sizeof(char**) * numberRows);
    verifyPointer(app, newList, "Problem malloc newList in copyListColumnsRows");
    for (i = 0; i < numberRows; i++) {
        newList[i] = malloc(sizeof(char*) * numberFields);
        verifyPointer(app, newList[i], "Problem malloc newList[i] in copyListColumns");
        for (j = 0; j < numberFields; j++) {
            newList[i][j] = malloc(sizeof(char) * (strlen(list[i][j]) + 1));
            verifyPointer(app, newList[i][j], "Problem malloc newList[i] in copyListColumns");
            strcpy(newList[i][j], list[i][j]);
        }
    }

    return newList;
}

Varchar *copyVarcharListFields(App *app, Varchar *listFields, unsigned int numberFields) {
    int i;
    Varchar *newListFields;

    newListFields = malloc(sizeof(Varchar) * numberFields);
    for (i = 0; i < numberFields; i++) {
        strcpy(newListFields[i], listFields[i]);
    }

    return newListFields;
}
