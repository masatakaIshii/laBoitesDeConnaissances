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

/**
*@brief To connect to the database and get result of select query
*
*@param (App *) app - structure of app to use mysql
*@param (const char *) currentQuery - the query for the database
*@param (unsigned int*) numberFields - pointer of number of fields
*@param (unsigned ind*) numberRows - pointer of number of rows
*@return (char ***) resultQuery - columns and rows of selection of query
*/
char ***querySelect (App *app, const char *currentQuery, unsigned int *numberFields, unsigned int *numberRows) {

    char ***resultQuery; //columns and row of select query
    MYSQL_RES *result; //store the informations of the query result
    int checkResult = 0; // check if mysql_query is success => 0, or fail => =!0

    checkResult = mysql_query(&app->mysql, currentQuery);
    verifyMYSQLIntResult(app, checkResult);

    result = mysql_store_result(&app->mysql);
    verifyPointer(app, result, mysql_error(&app->mysql));

    //get number of fields and row in result of query
    *numberFields = mysql_num_fields(result);
    *numberRows = mysql_num_rows(result);

    resultQuery = fetchQuerySelect(app, result, *numberFields, *numberRows);

    mysql_free_result(result);

    return resultQuery;
}
/**
*@brief Fetch the query's results in table of rows and fields
*
*@param (unsigned int*) numberFields - pointer of number of fields
*@param (unsigned ind*) numberRows - pointer of number of rows
*@return (char ***) resultFetch - columns and rows of selection of query
*/
char ***fetchQuerySelect(App *app, MYSQL_RES *result, unsigned int numberFields, unsigned int numberRows){
    char ***resultFetch; //columns and row of select query
    MYSQL_ROW row; // fetch result of each row
    unsigned long *lengths; //array of lengths of each fetch result of row
    int i = 0, j = 0;

    //malloc rows
    resultFetch = malloc(sizeof(char**) * numberRows);
    verifyPointer(app, resultFetch, "problem of allocation memory resultFetch");

    while((row = mysql_fetch_row(result))){
        if (row == NULL && strcmp(mysql_error(&app->mysql), "") != 0){
            verifyPointer(app, row, strcat("Error[MySQL] : ", mysql_error(&app->mysql)));
        }
        //get length of each value
        lengths = mysql_fetch_lengths(result);
        verifyPointer(app, lengths, strcat("Error[MySQL] : ", mysql_error(&app->mysql)));
        //malloc fields for each row
        resultFetch[i] = malloc(sizeof(char*) * numberFields);
        verifyPointer(app, resultFetch[i], "Problem allocation memory resultFetch[i]");
        for (j = 0; j < numberFields; j++) {
            resultFetch[i][j] = malloc(sizeof(char) * (lengths[j] + 1));
            verifyPointer(app, resultFetch[i][j], "problem of allocation memory resultFetch[i][j]");
            sprintf(resultFetch[i][j],(row[j] != NULL)?row[j]:"");
        }
        i++;
    }

    return resultFetch;
}
//TODO : prepared query select
