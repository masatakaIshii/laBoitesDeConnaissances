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
* To connect to the database and get result of select query
* @param (App *) app - structure of app to use mysql
* @param (const char *) currentQuery - the query for the database
* @param (unsigned int*) numberFields - pointer of number of fields
* @param (unsigned ind*) numberRows - pointer of number of rows
* @return (char ***) resultQuery - columns and rows of selection of query
*/
char ***querySelect (App *app, const char *currentQuery, unsigned int *numberFields, unsigned int *numberRows) {

    char ***resultQuery;
    MYSQL_RES *result;

    mysql_query(&app->mysql, currentQuery);

    result = mysql_store_result(&app->mysql);
    verifyPointer(app, result, mysql_error(&app->mysql));

    *numberFields = mysql_num_fields(result);
    *numberRows = mysql_num_rows(result);

    resultQuery = fetchQuerySelect(result, *numberFields, *numberRows);

    mysql_free_result(result);

    return resultQuery;
}

char ***fetchQuerySelect(MYSQL_RES *result, unsigned int numberFields, unsigned int numberRows){

    char ***resultFetch;
    MYSQL_ROW row;
    unsigned long *lengths;
    int i = 0, j = 0;

    resultFetch = malloc(sizeof(char**) * numberRows);
    if (resultFetch == NULL) exit(0);

    while((row = mysql_fetch_row(result))){
        //get length of each value
        lengths = mysql_fetch_lengths(result);
        resultFetch[i] = malloc(sizeof(char*) * numberFields);
        if (resultFetch[i] == NULL) exit(-1);
        //put all values of select query in resultFetch
        for (j = 0; j < numberFields; j++) {
            resultFetch[i][j] = malloc(sizeof(char) * (lengths[j] + 1));
            if (resultFetch[i][j] == NULL) exit(-1);
            sprintf(resultFetch[i][j],(row[j] != NULL)?row[j]:"");
        }
        i++;
    }

    return resultFetch;
}
//TODO : prepared query select
