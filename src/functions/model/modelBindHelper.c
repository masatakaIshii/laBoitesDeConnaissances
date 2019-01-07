/*
** Filename : modelBindHelper.c
**
** Made by  : Masataka ISHII
**
** Description  : functions used API C MySQL for bind input and output prepared queries
*/

#include "../../headers/model/modelBindHelper.h"

void setBindParams(App *app, char **paramsValues) {
    int                 result = 0;
    BindType            bindIO = BIND_INPUT;
    MySqlStmtManager    *stmtManager = &app->model.query.stmtManager;

    stmtManager->BindInOut = bindIO;

    loadBindParams(app, stmtManager, bindIO, paramsValues);

    result = mysql_stmt_bind_param(stmtManager->stmt, stmtManager->buffersBind);
    verifyStmtIntResult(app, stmtManager, "Problem in mysql_stmt_bind_param in setBindParams", result);
}

void bindSelectQueryPrepared(App *app, MySqlStmtManager *stmtManager, SelectQuery *selectQuery) {

    BindType    bindIO = BIND_OUTPUT;

    stmtManager->numberParams = selectQuery->numberFields;

    stmtManager->BindInOut = bindIO;

    loadBindParams(app, stmtManager, bindIO, NULL);
}

void loadBindParams(App *app, MySqlStmtManager *stmtManager, BindType bindIO, char **paramsValues){
    int                 i;
    enum_field_types    typeParam;
    Varchar             currentParamValue;

    stmtManager->params = malloc(sizeof(MySqlParamsBind) * stmtManager->numberParams);
    for (i = 0; i < stmtManager->numberParams; i++) {

        typeParam = stmtManager->buffersBind[i].buffer_type;

        if (paramsValues != NULL) {
            strcpy(currentParamValue, paramsValues[i]);
        } else {
            strcpy(currentParamValue, "");
        }

        if (typeParam == MYSQL_TYPE_BLOB || typeParam == MYSQL_TYPE_STRING || typeParam == MYSQL_TYPE_VAR_STRING){
            preparedBindParamString(app, i, stmtManager, currentParamValue, bindIO);
        }
        if (typeParam == MYSQL_TYPE_LONG || typeParam == MYSQL_TYPE_SHORT || typeParam == MYSQL_TYPE_TINY) {
            preparedBindParamInt(app, i, stmtManager, currentParamValue, bindIO);
        }
        if (typeParam == MYSQL_TYPE_DATE || typeParam == MYSQL_TYPE_DATETIME || typeParam == MYSQL_TYPE_TIMESTAMP) {
            preparedBindParamDate(app, i, stmtManager, currentParamValue, bindIO);
        }
        if (typeParam == MYSQL_TYPE_DOUBLE) {
            preparedBindParamDouble(app, i, stmtManager, currentParamValue, bindIO);
        }
    }
}

/**
*function to bind string parameter if the bind's type is input
*
*@param (App *) app - pointer of structure of application
*@param (int) index - index of the param that the type is string
*@param (MysqlStmtManager *) - pointer of structure for stock stmt query's informations
*@param (char *) paramValue - string value
*@param (BindType) bindIO - if the bind step is input (data values sent to the server) or output (result values returned from the server)
*/
void preparedBindParamString(App *app, int index, MySqlStmtManager *stmtManager, char *paramValue, BindType bindIO) {

    if (bindIO == BIND_INPUT) {
        stmtManager->params[index].paramsLengths = strlen(paramValue);
        stmtManager->params[index].paramsIsNull = (strncmp(paramValue, "", strlen(paramValue)) == 0) ? 1 : 0;

        stmtManager->params[index].paramsString = malloc(sizeof(char) * (strlen(paramValue) + 1));
        verifyPointer(app, stmtManager->params[index].paramsString, "Problem malloc stmtManager->params[index].paramsString in preparedBindParamString\n");
        strcpy(stmtManager->params[index].paramsString, paramValue);
    }

    bindParamString(index, stmtManager, bindIO);
}

/**
*function to bind int parameter if the bind's type is input

*
*@param (App *) app - pointer of structure of application
*@param (int) index - index of the param that the type is int
*@param (MysqlStmtManager *) - pointer of structure for stock stmt query's informations
*@param (char *) paramValue - string to transform to int value
*@param (BindType) bindIO - if the bind step is input (data values sent to the server) or output (result values returned from the server)
*/
void preparedBindParamInt(App *app, int index, MySqlStmtManager *stmtManager, char *paramValue, BindType bindIO) {

    if (bindIO == BIND_INPUT) {
        stmtManager->params[index].paramsIsNull = (strncmp(paramValue, "", strlen(paramValue)) == 0) ? 1 : 0;
        stmtManager->params[index].paramNumber = atoi(paramValue);

        if (stmtManager->params[index].paramsIsNull == 0) {
            if (atoi(paramValue) == 0 && paramValue[0] != '0') {
                printf("Problem with paramValue and its type\n");
                quitApp(app);
            }
        }
    }

    bindParamInt(index, stmtManager, bindIO);
}

/**
*function to bind datetime parameter if the bind's type is input
*
*@param (App *) app - pointer of structure of application
*@param (int) index - index of the param that the type is datetime
*@param (MysqlStmtManager *) - pointer of structure for stock stmt query's informations
*@param (char *) paramValue - string to transform to few datetime values
*@param (BindType) bindIO - if the bind step is input (data values sent to the server) or output (result values returned from the server)
*/
void preparedBindParamDate(App *app, int index, MySqlStmtManager *stmtManager, char *paramValue, BindType bindIO) {

    if (bindIO == BIND_INPUT) {
        MYSQL_TIME *time = &stmtManager->params[index].paramsDateTime;
        stmtManager->params[index].paramsIsNull = (strncmp(paramValue, "", strlen(paramValue)) == 0) ? 1 : 0;

        if (stmtManager->params[index].paramsIsNull == 0){
            sscanf(paramValue, "%u-%u-%u %u:%u:%u", &time->year, &time->month, &time->day, &time->hour, &time->minute, &time->second);
        }
        time->second_part = 0;
    }

    bindParamDate(index, stmtManager, bindIO);
}
/**
*function to bind double parameter if the bind's type is input
*
*@param (App *) app - pointer of structure of application
*@param (int) index - index of the param that the type is double
*@param (MysqlStmtManager *) - pointer of structure for stock stmt query's informations
*@param (char *) paramValue - string to convert to double
*@param (BindType) bindIO - if the bind step is input (data values sent to the server) or output (result values returned from the server)
*/
void preparedBindParamDouble(App *app, int index, MySqlStmtManager *stmtManager, char *paramValue, BindType bindIO) {

    if (bindIO == BIND_INPUT) {
        stmtManager->params[index].paramDouble = atof(paramValue);
        stmtManager->params[index].paramsIsNull = (strncmp(paramValue, "", strlen(paramValue)) == 0) ? 1 : 0;

        if (stmtManager->params[index].paramsIsNull == 0) {
            if (atof(paramValue) == 0 && paramValue[0] != '0') {
                printf("Problem with paramValue and its type\n");
                quitApp(app);
            }
        }
    }

    bindParamDouble(index, stmtManager, bindIO);
}

void bindParamString(int index, MySqlStmtManager *stmtManager, BindType bindIO) {

    if (bindIO == BIND_OUTPUT){
        //buffer = 0 because for get precise length of string value after fetch
        stmtManager->buffersBind[index].buffer_length = 0;
        stmtManager->buffersBind[index].buffer = 0;
        stmtManager->buffersBind[index].is_null = (my_bool*)&stmtManager->params[index].paramsIsNull;
        stmtManager->buffersBind[index].error = (my_bool*)&stmtManager->params[index].paramError;
    }

    if (bindIO == BIND_INPUT) {
        stmtManager->buffersBind[index].buffer_length = stmtManager->params[index].paramsLengths + 1;
        stmtManager->buffersBind[index].buffer = (char *)stmtManager->params[index].paramsString;

        if (stmtManager->params[index].paramsIsNull != 0) {
            stmtManager->buffersBind[index].is_null = (my_bool*)&stmtManager->params[index].paramsIsNull;
        } else {
            stmtManager->buffersBind[index].is_null = 0;
        }
    }
    stmtManager->buffersBind[index].length = &stmtManager->params[index].paramsLengths;
}

void bindParamInt(int index, MySqlStmtManager *stmtManager, BindType bindIO) {

    if (bindIO == BIND_OUTPUT) {
        stmtManager->buffersBind[index].is_null = (my_bool*)&stmtManager->params[index].paramsIsNull;
        stmtManager->buffersBind[index].length = &stmtManager->params[index].paramsLengths;
        stmtManager->buffersBind[index].error = (my_bool*)&stmtManager->params[index].paramError;
    }

    if (bindIO == BIND_INPUT) {
        if (stmtManager->params[index].paramsIsNull == 1) {
            stmtManager->buffersBind[index].is_null = (my_bool*)&stmtManager->params[index].paramsIsNull;
        } else {
            stmtManager->buffersBind[index].is_null = 0;
        }
        stmtManager->buffersBind[index].length = 0;
    }

    stmtManager->buffersBind[index].buffer = (void *)&stmtManager->params[index].paramNumber;
}

void bindParamDate(int index, MySqlStmtManager *stmtManager, BindType bindIO) {

    if (bindIO == BIND_OUTPUT) {
        stmtManager->buffersBind[index].is_null = (my_bool*)&stmtManager->params[index].paramsIsNull;
        stmtManager->buffersBind[index].length = &stmtManager->params[index].paramsLengths;
        stmtManager->buffersBind[index].error = (my_bool*)&stmtManager->params[index].paramError;
    }

    if (bindIO == BIND_INPUT) {
        if (stmtManager->params[index].paramsIsNull == 1) {
            stmtManager->buffersBind[index].is_null = (my_bool*)&stmtManager->params[index].paramsIsNull;
        } else {
            stmtManager->buffersBind[index].is_null = 0;
        }
        stmtManager->buffersBind[index].length = 0;
    }

    stmtManager->buffersBind[index].buffer = (char *)&stmtManager->params[index].paramsDateTime;
}

void bindParamDouble(int index, MySqlStmtManager *stmtManager, BindType bindIO) {

    if (bindIO == BIND_OUTPUT) {
        stmtManager->buffersBind[index].is_null = (my_bool*)&stmtManager->params[index].paramsIsNull;
        stmtManager->buffersBind[index].length = &stmtManager->params[index].paramsLengths;
        stmtManager->buffersBind[index].error = (my_bool*)&stmtManager->params[index].paramError;
    }

    if (bindIO == BIND_INPUT) {
        if (stmtManager->params[index].paramsIsNull == 1) {
            stmtManager->buffersBind[index].is_null = (my_bool*)&stmtManager->params[index].paramsIsNull;
        } else {
            stmtManager->buffersBind[index].is_null = 0;
        }
        stmtManager->buffersBind[index].length = 0;
    }

    stmtManager->buffersBind[index].buffer = (void *)&stmtManager->params[index].paramDouble;
}
