/*
** Filename : modelQuit.c
**
** Made by  : Masataka ISHII
**
** Description  : functions to free all memory allocation concern to MYSQL API
*/

#include "../../headers/model/modelQuit.h"

void freeSelectQuery(App *app) {
    SelectQuery *selectQuery = &app->model.query.selectQuery;
    if (selectQuery != NULL) {
        freeResultStringTable(selectQuery->listColumnsRows, selectQuery->numberFields, selectQuery->numberRows);
        selectQuery->listColumnsRows = NULL;
        freeListString(&selectQuery->listFields);
        selectQuery->listFields = NULL;
    }
}

/**
*@brief Free list of fields
*
*@param fieldsList : list of string content fields name
*@param numberFields : number of fields that content the list
*/
void freeListString(Varchar **fieldsList) {

    if (*fieldsList != NULL) {
        free(*fieldsList);
        *fieldsList = NULL;
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
void freeStructTableMysql(Model *model) {
    int i;

    if (model->tables != NULL) {
        for (i = 0; i < model->numberAllTables; i++) {
            free(model->tables[i].listFieldsTypes);
            freeListString(&model->tables[i].listFieldsNames);
            model->tables[i].listFieldsNames = NULL;
            model->tables[i].numberField = 0;
            strcpy(model->tables[i].tableName, "");
        }
        free(model->tables);
        model->tables = NULL;
    }

}

void quitModel(Model *model) {

    if (model->listAllTables != NULL) {
        freeListString(&model->listAllTables);
    }

    quitSelectQuery(&model->query.selectQuery);

    quitStmtManager(&model->query.stmtManager);

    if (model->tables != NULL) {
        freeStructTableMysql(model);
        //remove(numberNamesStructTables);
    }

    if (model->ifMysqlIsInit != 0) {
        mysql_close(model->mysql);
        model->ifMysqlIsInit = 0;
    }

}

void quitSelectQuery(SelectQuery *selectQuery) {

    unsigned int numberRows = 0;
    unsigned int numberFields = 0;

    if (selectQuery->listColumnsRows != NULL) {
        numberRows = selectQuery->numberRows;
        numberFields = selectQuery->numberFields;
        freeResultStringTable(selectQuery->listColumnsRows, numberFields, numberRows);
        if (selectQuery->listFields != NULL) {
            freeListString(&selectQuery->listFields);
        }
        selectQuery->resultWithFieldsList = 0;
    }
}

/**
*@brief To free all stmt fields in structure stmtManager
*
*@param (MySqlStmtManager *) - stmtManager : structure for prepared query
*/
void quitStmtManager(MySqlStmtManager *stmtManager) {

    if (stmtManager->ifStmtIsInit != 0) {
        mysql_stmt_close(stmtManager->stmt);
        stmtManager->ifStmtIsInit = 0;
    }

    if (stmtManager->numberParams != 0) {
        if (stmtManager->paramsNames != NULL) {
            free(stmtManager->paramsNames);
            printf("ca free stmtManager->paramsNames\n");
        }
        if (stmtManager->params != NULL) {
            free(stmtManager->params);
            printf("ca free stmtManager->params\n");
        }
        if (stmtManager->buffersBind != NULL) {
            free(stmtManager->buffersBind);
            printf("ca free stmtManager->params\n");
        }
        stmtManager->numberParams = 0;
    }

    if (stmtManager->numberTables != 0) {
        if (stmtManager->tablesNames != NULL) {
            free(stmtManager->tablesNames);
            printf("ca free stmtManager->tablesNames\n");
        }
        stmtManager->numberTables = 0;
    }
}
