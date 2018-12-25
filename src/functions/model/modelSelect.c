/*
** Filename : modelSelect.c
**
** Made by  : Masataka ISHII
**
** Description  : select functions used API C MySQL for select data in database
*/
#include <stdio.h>
#include "../../headers/common.h"
#include "../../headers/struct.h"
#include "../../headers/model/modelSelect.h"
#include <errno.h>

/**
*@brief To connect to the database and get result of select query
*
*@param (App *) app - structure of app to use mysql
*@param (const char *) currentQuery - the query for the database
*@param (unsigned int*) numberFields - pointer of number of fields
*@param (unsigned ind*) numberRows - pointer of number of rows
*@return (char ***) resultQuery - columns and rows of selection of query
*/

void getSelectQuery (App *app, const char *currentQuery, SelectQuery *selectQuery) {

    int checkResult = 0; // check if mysql_query is success => 0, or fail => =!0
    int i;

    checkResult = mysql_query(app->model.mysql, currentQuery);
    verifyMYSQLIntResult(app, checkResult);


    selectQuery->result = mysql_store_result(app->model.mysql);
    verifyPointer(app, selectQuery->result, mysql_error(app->model.mysql));


    //get number of fields and row in result of query
    selectQuery->numberFields = mysql_num_fields(selectQuery->result);
    selectQuery->numberRows = mysql_num_rows(selectQuery->result);

    fetchFieldsOfQuerySelect(app, selectQuery);

    fetchQuerySelect(app, selectQuery);

    mysql_free_result(selectQuery->result);
}

void fetchFieldsOfQuerySelect(App *app, SelectQuery *selectQuery) {

    int i;
    short moreThanOneTable = 0;
    char temp[100];
    MYSQL_FIELD *fields = mysql_fetch_fields(selectQuery->result);

    selectQuery->listFields = malloc(sizeof(char *) * selectQuery->numberFields);

    verifyPointer(app, selectQuery->listFields, "Problem memory allocation at selectQuery->listFieldss");

    moreThanOneTable = checkIfQueryConcernMoreThan1Table(fields, selectQuery->numberFields);

    //printf("\nfetchFieldsOfQuerySelect\n");
    for (i = 0; i < selectQuery->numberFields; i++) {

        if (moreThanOneTable) {
            strcpy(temp, fields[i].table);
            strcat(temp, ".");
            selectQuery->listFields[i] = malloc(sizeof(char) * (strlen(fields[i].name) + strlen(fields[i].name) + 1));
            strcpy(selectQuery->listFields[i], strcat(temp, fields[i].name));

        } else {
            selectQuery->listFields[i] = malloc(sizeof(char) * (strlen(fields[i].name) + 1));
            strcpy(selectQuery->listFields[i], fields[i].name);
        }
    }
}

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
    selectQuery->listColumnsRows = malloc(sizeof(selectQuery->listColumnsRows) * selectQuery->numberRows);

    verifyPointer(app, selectQuery->listColumnsRows, "problem of allocation memory selectQuery->listColumnsRows\n");
    while((row = mysql_fetch_row(selectQuery->result))){

        if (row == NULL && strcmp(mysql_error(app->model.mysql), "") != 0){
            verifyPointer(app, row, strcat("Error[MySQL] : ", mysql_error(app->model.mysql)));
        }

        //get length of each value
        lengths = mysql_fetch_lengths(selectQuery->result);

        fetchOneRowQuerySelect(app, selectQuery, lengths, row, i);

        printf("\n");
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

void addFieldsToResult(App *app, SelectQuery *selectQuery) {
    char ***inter;
    int i;
    int j;
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
            inter[i] = copyListString(app, selectQuery->listFields, selectQuery->numberFields);
        } else {
            inter[i] = copyListString(app, selectQuery->listColumnsRows[i - 1], selectQuery->numberFields);
        }
    }

    freeResultStringTable(selectQuery->listColumnsRows, selectQuery->numberFields, selectQuery->numberRows - 1);
    selectQuery->listColumnsRows = inter;

    selectQuery->resultWithFieldsList = 1;
}

void removeFieldsInResult(App *app, SelectQuery *selectQuery) {
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

    freeResultStringTable(selectQuery->listColumnsRows, selectQuery->numberFields, selectQuery->numberRows + 1);
    selectQuery->listColumnsRows = inter;

    selectQuery->resultWithFieldsList = 0;
}

char **copyListString(App *app, char **listString, unsigned int numberFields) {
    char **copyList;
    int i;

    copyList = malloc(sizeof(char*) * numberFields);

    verifyPointer(app, copyList, "Problem malloc in copyList in the function copyListString\n");

    for (i = 0; i < numberFields; i++) {

        copyList[i] = malloc(sizeof(char) * (strlen(listString[i]) + 1));
        verifyPointer(app, copyList[i], "Problem malloc in copyList[i] in the function copyListString\n");
        strcpy(copyList[i], (listString[i] == NULL) ? "" : listString[i]);
    }

    return copyList;
}
//TODO : prepared query select
