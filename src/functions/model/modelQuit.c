/*
** Filename : mysqlQuit.c
**
** Made by  : Masataka ISHII
**
** Description  : functions to free all memory allocation concern to MYSQL API
*/

#include "../../headers/model/modelQuit.h"
#include "../../headers/struct.h"

void freeSelectQuery(SelectQuery *selectQuery) {
    int i, j;

    if (selectQuery != NULL) {
        freeResultStringTable(selectQuery->listColumnsRows, selectQuery->numberFields, selectQuery->numberRows);
        freeListString(selectQuery->listFields, selectQuery->numberFields);
    }
}

/**
*@brief Free list of fields
*
*@param fieldsList : list of string content fields name
*@param numberFields : number of fields that content the list
*/
void freeListString(char **fieldsList, unsigned int numberFields) {
    int i;

    if (fieldsList != NULL) {
        for (i = 0; i < numberFields; i++) {
            free(fieldsList[i]);
        }
        free(fieldsList);
    }
}

/**
*@brief Free table content rows and fields (double array of string)
*
*@param stringTable : table to free
*@param numberFields : number of field of table
*@param numberRows : number of rows of table
*/
void freeResultStringTable(char ***stringTable, unsigned int numberFields, unsigned int numberRows) {
    int i;
    int j;

    if (stringTable != NULL) {
        for (i = 0; i < numberRows; i++) {
            for (j = 0; j < numberFields; j++) {
                free(stringTable[i][j]);
            }
            free(stringTable[i]);
        }
        free(stringTable);
    }
}

/**
*@brief free array dynamic of structure TableMysql
*
*@param tables : TableMysql structure that content table informations
*@param numberTables : number of TableMysql structure
*/
void freeStructTableMysql(MySqlTable **tables, int numberTables) {
    int i;

    if (tables != NULL) {
        for (i =0; i < numberTables; i++) {
            freeListString(tables[i]->listFieldsNames, tables[i]->numberField);

            if (tables[i]->listFieldsTypes != NULL) {

                free(tables[i]->listFieldsTypes);
            }
        }
    }
}

/**
*@brief To free all stmt fields in structure stmtManager
*
*@param (MySqlStmtManager *) - stmtManager : structure for prepared query
*/
void quitStmtManager(MySqlStmtManager *stmtManager) {

    if (stmtManager->buffersBind != NULL) {
        free(stmtManager->buffersBind);
    }

    if (mysql_stmt_free_result(stmtManager->stmt) != 0) {
        printf("Problem with free result");
    }

    if (mysql_stmt_close(stmtManager->stmt) != 0) {
        printf("Problem with close mysql stmt\n");
    }
}
