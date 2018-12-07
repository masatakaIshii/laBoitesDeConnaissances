/*
** Filename : mysqlCommon.c
**
** Made by  : Masataka ISHII
**
** Description  : common functions used API C MySQL
*/
#include <stdio.h>
#include "../../headers/model/modelCommon.h"
#include

void dbConnect(MYSQL* mysql) {
    mysql_init(mysql);
    mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "option");

    mysql_real_connect(mysql, "127.0.0.1", "root", "root", "the_box_of_knowledge", 0, NULL, 0), mysql);
}

void checkMYSQLError(void *functionResult, MYSQL* mysql) {
    if(functionResult == NULL) {
        if(*mysql_error(mysql)){

            fprintf(stderr, "%s", mysql_error(mysql));
            exit(1);
        }
    }
}

char **getFieldsNameType(MYSQL* mysql, const char *table, unsigned int* numberFields) {
    char **fieldsNameType;
    MYSQL_RES *resultFields;
    unsigned int fieldsCount;

    checkMYSQLError(resultFields = mysql_list_fields(mysql, table, NULL), mysql);

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
