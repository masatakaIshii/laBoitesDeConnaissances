/*
** Filename : modelBindHelper.c
**
** Made by  : Masataka ISHII
**
** Description  : functions used API C MySQL for bind prepared queries
*/

#include "../../headers/model/modelBindHelper.h"
void setBindParams(App *app, char **paramsValues) {

    MySqlStmtManager *stmtManager = &app->model.query.stmtManager;

    loadBindParams(app, stmtManager, paramsValues);

    if (mysql_stmt_bind_param(stmtManager->stmt, stmtManager->buffersBind)) {
        printf("Error[MYSQL_STMT_BIND] : %s\n", mysql_stmt_error(stmtManager->stmt));
        quitApp(app);
        exit(EXIT_FAILURE);
    }
}

void loadBindParams(App *app, MySqlStmtManager *stmtManager, char **paramsValues){
    int i;
    enum_field_types typeParam;

    stmtManager->params = malloc(sizeof(MySqlParamsBind) * stmtManager->numberParams);
    for (i = 0; i < stmtManager->numberParams; i++) {

        typeParam = stmtManager->buffersBind[i].buffer_type;
        if (typeParam == MYSQL_TYPE_BLOB || typeParam == MYSQL_TYPE_STRING || typeParam == MYSQL_TYPE_VAR_STRING){
            bindParamString(app, i, stmtManager, paramsValues[i]);
        }

        if (typeParam == MYSQL_TYPE_LONG || typeParam == MYSQL_TYPE_SHORT || typeParam == MYSQL_TYPE_TINY) {
            bindParamInt(app, i, stmtManager, paramsValues[i]);
        }

        if (typeParam == MYSQL_TYPE_DATE || typeParam == MYSQL_TYPE_DATETIME || typeParam == MYSQL_TYPE_TIMESTAMP) {
            bindParamDate(app, i, stmtManager, paramsValues[i]);
        }

        if (typeParam == MYSQL_TYPE_DOUBLE) {
            bindParamDouble(app, i, stmtManager, paramsValues[i]);
        }
    }
}

void bindParamString(App *app, int index, MySqlStmtManager *stmtManager, char *paramValue) {
    stmtManager->params[index].paramsLengths = strlen(paramValue);
    stmtManager->params[index].paramsIsNull = (strncmp(paramValue, "", strlen(paramValue)) == 0) ? 1 : 0;

    stmtManager->params[index].paramsString = malloc(sizeof(char) * (strlen(paramValue) + 1));
    strcpy(stmtManager->params[index].paramsString, paramValue);

    stmtManager->buffersBind[index].buffer_length = stmtManager->params[index].paramsLengths + 1;
    stmtManager->buffersBind[index].buffer = (char *)stmtManager->params[index].paramsString;
    if (stmtManager->params[index].paramsIsNull == 1) {
        stmtManager->buffersBind[index].is_null = (my_bool*)&stmtManager->params[index].paramsIsNull;
    } else {
        stmtManager->buffersBind[index].is_null = 0;
    }
    stmtManager->buffersBind[index].length = &stmtManager->params[index].paramsLengths;

    printf("buffer : %s\n", stmtManager->buffersBind[index].buffer);
}

void bindParamInt(App *app, int index, MySqlStmtManager *stmtManager, char *paramValue) {
    stmtManager->params[index].paramsIsNull = (strncmp(paramValue, "", strlen(paramValue)) == 0) ? 1 : 0;
    stmtManager->params[index].paramNumber = atoi(paramValue);

    if (stmtManager->params[index].paramsIsNull == 1) {
        if (atoi(paramValue) == 0 && paramValue[0] != '0') {
            printf("Problem with paramValue and its type\n");
            quitApp(app);
        }
    }

    stmtManager->buffersBind[index].buffer = (void *)&stmtManager->params[index].paramNumber;
    if (stmtManager->params[index].paramsIsNull == 1) {
        stmtManager->buffersBind[index].is_null = (my_bool*)&stmtManager->params[index].paramsIsNull;
    } else {
        stmtManager->buffersBind[index].is_null = 0;
    }
    stmtManager->buffersBind[index].length = 0;
}

void bindParamDate(App *app, int index, MySqlStmtManager *stmtManager, char *paramValue) {
    MYSQL_TIME *time = &stmtManager->params[index].paramsDateTime;
    stmtManager->params[index].paramsIsNull = (strncmp(paramValue, "", strlen(paramValue)) == 0) ? 1 : 0;

    if (stmtManager->params[index].paramsIsNull == 0){
        sscanf(paramValue, "%u-%u-%u %u:%u:%u", &time->year, &time->month, &time->day, &time->hour, &time->minute, &time->second);
    }
    stmtManager->buffersBind[index].buffer = (void *)time;
    if (stmtManager->params[index].paramsIsNull == 1) {
        stmtManager->buffersBind[index].is_null = (my_bool*)&stmtManager->params[index].paramsIsNull;
    } else {
        stmtManager->buffersBind[index].is_null = 0;
    }
    stmtManager->buffersBind[index].length = 0;
}

void bindParamDouble(App *app, int index, MySqlStmtManager *stmtManager, char *paramValue) {
    stmtManager->params[index].paramDouble = atof(paramValue);
    stmtManager->params[index].paramsIsNull = (strncmp(paramValue, "", strlen(paramValue)) == 0) ? 1 : 0;

    if (stmtManager->params[index].paramsIsNull == 0) {
        if (atof(paramValue) == 0 && paramValue[0] != '0') {
            printf("Problem with paramValue and its type\n");
            quitApp(app);
        }
    }
    stmtManager->buffersBind[index].buffer = (void *)&stmtManager->params[index].paramDouble;
    if (stmtManager->params[index].paramsIsNull == 1) {
        stmtManager->buffersBind[index].is_null = (my_bool*)&stmtManager->params[index].paramsIsNull;
    } else {
        stmtManager->buffersBind[index].is_null = 0;
    }

    stmtManager->buffersBind[index].length = 0;
}
