/*
** Filename : mysqlCommon.c
**
** Made by  : Masataka ISHII
**
** Description  : common functions used API C MySQL
*/
#include <stdio.h>
#include "../../headers/model/modelCommon.h"
#include "../../headers/common.h"
#include <mysql.h>
#include <SDL2/SDL.h>

void dbConnect(App *app) {

    mysql_options(&app->mysql, MYSQL_READ_DEFAULT_GROUP, "option");

    mysql_real_connect(&app->mysql, "127.0.0.1", "root", "", "the_box_of_knowledge", 0, NULL, 0);
    if (!(&app->mysql)) {
        printf("%s", mysql_error(&app->mysql));
    }
}

char **getFieldsNameType(App *app, const char *table, unsigned int* numberFields) {
    char **fieldsNameType;
    MYSQL_RES *resultFields;
    unsigned int fieldsCount;

    resultFields = mysql_list_fields(&app->mysql, table, NULL);
    verifyPointer(app, resultFields, mysql_error(&app->mysql));

    fieldsCount = mysql_num_fields(resultFields);

    if (numberFields != NULL) {
        *numberFields = fieldsCount;
    }

    printf("Number of columns : %d\n", fieldsCount);

    fieldsNameType = fetchFieldsNameType(resultFields, fieldsCount);

    return fieldsNameType;
}

char **fetchFieldsNameType(MYSQL_RES *result, unsigned int numberFields){
    char **fieldsNameType;
    MYSQL_FIELD *fetchField;
    int i;

    fieldsNameType = malloc(sizeof(char*) * numberFields);
    for (i = 0; i < numberFields; i++) {
        fetchField = mysql_fetch_field_direct(result, i);
        fieldsNameType[i] = malloc(sizeof(char) * fetchField->name_length);
        strcpy(fieldsNameType[i], fetchField->name);
    }

    return fieldsNameType;
}

char ***mallocStringTable(unsigned int numberRows,unsigned int numberFields) {
    char *** stringTable;
    int i;

    stringTable = malloc(sizeof(char**) * numberRows);
    if (stringTable == NULL) {
        printf("Memory allocation problem in numberRows");
        exit(1);
    }
    for (i = 0; i < numberRows; i++) {
        *(stringTable + i) = malloc(sizeof(char*) * numberFields);
        if (*(stringTable + i) == NULL) {
            printf("Memory allocation problem in numberFields");
            exit(1);
        }
    }

    return stringTable;
}

void freeFieldsList(char* **fieldsList, unsigned int numberFields) {
    int i;

    for (i = 0; i < numberFields; i++) {
        free((*fieldsList)[i]);
    }
    free(*fieldsList);
}

void freeResultStringTable(char* ***stringTable, unsigned int numberFields, unsigned int numberRows) {
    int i;
    int j;

    for (i = 0; i < numberRows; i++) {
        for (j = 0; j < numberFields; j++) {
            free((*stringTable)[i][j]);
        }
        free((*stringTable)[i]);
    }
    free(*stringTable);
}
