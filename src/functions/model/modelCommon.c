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

void dbConnect(App *app) {

    mysql_options(&app->mysql, MYSQL_READ_DEFAULT_GROUP, "option");

    mysql_real_connect(&app->mysql, "127.0.0.1", "root", "root", "the_box_of_knowledge", 0, NULL, 0);
    if (!(&app->mysql)) {
        printf("%s", mysql_error(&app->mysql));
    }
}

void verifyMYSQLPointer(App *app, void *pointer) {
    if (!pointer) {
        printf("%s", mysql_error(&app->mysql));
        quitApp(app);
        exit(EXIT_FAILURE);
    }
}

void verifyMYSQLIntResult(App *app, int result) {
    if (result != 0) {
        printf("%s", mysql_error(&app->mysql));
        quitApp(app);
        exit(EXIT_FAILURE);
    }
}
/**
* To get array of fields name, possible to get unsigned int listMysqlType
* @param
*
*/
char **getFieldsName(App *app, const char *table, unsigned int* numberFields, unsigned int **listMysqlType) {
    char **fieldsName;
    MYSQL_RES *resultFields;
    unsigned int fieldsCount;


    resultFields = mysql_list_fields(&app->mysql, table, NULL);
    verifyPointer(app, resultFields, mysql_error(&app->mysql));

    fieldsCount = mysql_num_fields(resultFields);

    if (numberFields != NULL) {
        *numberFields = fieldsCount;
    }

    fieldsName = fetchFieldsName(resultFields, fieldsCount, listMysqlType);

    return fieldsName;
}

char **fetchFieldsName(MYSQL_RES *result, unsigned int numberFields, unsigned int **listMysqlType){
    char **fieldsName;
    MYSQL_FIELD *fetchField;
    int i;

    fieldsName = malloc(sizeof(char*) * numberFields);
    checkPointer(fieldsName, "problem allocation memory in fieldsName l.68");

    if (listMysqlType != NULL) {
        *listMysqlType = malloc(sizeof(unsigned int) * numberFields);
        checkPointer(fieldsName, "problem allocation memory in *listMysqlType l.72");
    }

    for (i = 0; i < numberFields; i++) {
        fetchField = mysql_fetch_field_direct(result, i);
        fieldsName[i] = malloc(sizeof(char) * fetchField->name_length);
        if (fieldsName[i] == NULL) {
            printf("problem memory allocation for fieldsName[i]");
            exit(EXIT_FAILURE);
        }
        if (listMysqlType != NULL) {
            (*listMysqlType)[i] = (unsigned int)fetchField->type;
        }
        strcpy(fieldsName[i], fetchField->name);
    }

    return fieldsName;
}

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

MYSQL_STMT *stmtInitialisation(App *app) {
    MYSQL_STMT *preparedQuery = mysql_stmt_init(&app->mysql);
    if (preparedQuery == NULL) {
        printf("Out of memory for prepared query");
        exit(EXIT_FAILURE);
    }

    return preparedQuery;
}

unsigned int getTypeOfField(App *app, char *field, char *table){
    unsigned int onetype, *listType;
    char **getList = getFieldsName(app, "user", NULL, &listType);



    return 1;
}

void getProperFieldAndTable(char **field, char **table) {
    char temp[255];
    if (strchr(*field, '.')) {
        strcpy(temp, *field);
        sprintf(*field, "%s", strchr(temp, '.') + 1);
        //vérifie si la table contient une valeur, si elle est NULL on affecte la table
        if (table && (*table) == NULL) {
            *table = malloc(sizeof(char) * (strlen(temp) + 1));
            *table = temp;
            (*table)[strchr(temp, '.') - temp] = '\0';
        }
    }
}

