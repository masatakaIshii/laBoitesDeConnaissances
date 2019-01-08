/*
** Filename : modelFetchSelectHelper.c
**
** Made by  : Masataka ISHII
**
** Description  : functions to fetch query and fill structure of SelectQuery
*/

#include "../../headers/model/modelFetchSelectHelper.h"

void fetchStmtToFillSelectQuery(App *app, MySqlStmtManager *stmtManager, SelectQuery *selectQuery){

    int result = 0;
    int i = 0;
    int j;

    result = mysql_stmt_bind_result(stmtManager->stmt, stmtManager->buffersBind);
    verifyStmtIntResult(app, stmtManager, "Problem in mysql_stmt_bind_result in bindSelectQueryPrepared", result);

    result = mysql_stmt_store_result(stmtManager->stmt);
    verifyStmtIntResult(app, stmtManager, "Problem in mysql_stmt_store_result in bindSelectQueryPrepared", result);

    selectQuery->numberRows = mysql_stmt_num_rows(stmtManager->stmt);

    selectQuery->listColumnsRows = malloc(sizeof(char **) * selectQuery->numberRows);
    verifyPointer(app, selectQuery->listColumnsRows, "Problem malloc selectQuery->listColumnsRows in fetchStmtToFillSelectQuery");

    for (i = 0; i < selectQuery->numberRows ; i++){
        mysql_stmt_fetch(stmtManager->stmt);

        selectQuery->listColumnsRows[i] = malloc(sizeof(char *) * selectQuery->numberFields);
        for(j = 0; j < selectQuery->numberFields; j++) {

            selectQuery->listColumnsRows[i][j] = getFetchValuesComparedToMysqlType(app, stmtManager, j);
        }
    }
}

char *getFetchValuesComparedToMysqlType(App *app, MySqlStmtManager *stmtManager, int indexColumn){

    char *result;
    int typeParam = stmtManager->buffersBind[indexColumn].buffer_type;

    if (stmtManager->params[indexColumn].paramsIsNull == 0) {
        if (typeParam == MYSQL_TYPE_LONG){
            copyNumberToString(app, &result, "%d", indexColumn, stmtManager);
        }
        if (typeParam == MYSQL_TYPE_DOUBLE) {
            copyNumberToString(app, &result, "%.2lf", indexColumn, stmtManager);
        }
        if (typeParam == MYSQL_TYPE_DATETIME) {
            copyDateTimeToString(app, &result, indexColumn, stmtManager);
        }
        if (typeParam == MYSQL_TYPE_VAR_STRING || typeParam == MYSQL_TYPE_STRING) {
            copyStringAfterFetchLength(app, &result, indexColumn, stmtManager);
        }
    } else {
        result = malloc(sizeof(char));
        strcpy(result, "");
    }

    return result;
}

void copyNumberToString(App *app, char **stringToFill, char *format, int index, MySqlStmtManager *stmtManager) {
    Text temp;

    if (strncmp(format, "%d", strlen("%d")) == 0 ) {
        sprintf(temp, format, stmtManager->params[index].paramNumber);
    }
    if (strncmp(format, "%.2lf", strlen("%.2lf")) == 0) {
        sprintf(temp, format, stmtManager->params[index].paramDouble);
    }

    *stringToFill = malloc(sizeof(char) * (strlen(temp) + 1));
    verifyPointer(app, *stringToFill, "Problem malloc *stringToFill in copyNumberToString\n");

    strcpy(*stringToFill, temp);
}

void copyDateTimeToString(App *app, char **stringToFill, int index, MySqlStmtManager *stmtManager) {
    Text temp;
    MYSQL_TIME ts;

    ts.year = stmtManager->params[index].paramsDateTime.year;
    ts.month = stmtManager->params[index].paramsDateTime.month;
    ts.day = stmtManager->params[index].paramsDateTime.day;
    ts.hour = stmtManager->params[index].paramsDateTime.hour;
    ts.minute = stmtManager->params[index].paramsDateTime.minute;
    ts.second = stmtManager->params[index].paramsDateTime.second;

    sprintf(temp, "%u-%u-%u %u:%u:%u", ts.year, ts.month, ts.day, ts.hour, ts.minute, ts.second);

    *stringToFill = malloc(sizeof(char) * (strlen(temp) + 1));
    verifyPointer(app, *stringToFill, "Problem malloc *stringToFill in copyDateTImeToString\n");

    strcpy(*stringToFill, temp);
}

void copyStringAfterFetchLength(App *app, char **stringToFill, int index, MySqlStmtManager *stmtManager) {
    unsigned long length = stmtManager->params[index].paramsLengths;

    *stringToFill = malloc(length + 1);
    verifyPointer(app, *stringToFill, "Problem malloc *stringToFill in copyStringAfterFetchLength\n");

    stmtManager->buffersBind[index].buffer = *stringToFill;
    stmtManager->buffersBind[index].buffer_length = length + 1;
    mysql_stmt_fetch_column(stmtManager->stmt, &stmtManager->buffersBind[index], index, 0);
    (*stringToFill)[length] = '\0';

}
//
//int getLengthStringOfInt (int intNumber) {
//    int length = 0;
//
//    while(1) {
//        if (abs(intNumber) == 0) {
//            length++;
//            break;
//        }
//        if (abs(intNumber) > round(pow((double)10, (double)length))){
//            length++;
//        }
//
//        if (abs(intNumber) < round(pow((double)10, (double)length))) {
//            break;
//        }
//        if (abs(intNumber) == round(pow((double)10, (double)length))) {
//            length++;
//            break;
//        }
//    }
//    if (number < 0) {
//        length++;
//    }
//    return length;
//}
