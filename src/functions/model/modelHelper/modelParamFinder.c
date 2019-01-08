/*
** Filename : modelParamFinder.c
**
** Made by  : Masataka ISHII
**
** Description  : functions to get fields names of parameters of query
*/
#include "../../../headers/model/modelHelper/modelParamFinder.h"

void getParamsNames(App *app, MySqlStmtManager *stmtManager, char *query, int numberParams) {

    if (strncmp("INSERT", query, strlen("INSERT")) == 0) {
        getParamsNamesInsert(app, stmtManager, query, numberParams);
    } else {
        getParamsNamesSelectUpdateDelete(app, stmtManager, query, numberParams);
    }
}

void getParamsNamesInsert(App *app, MySqlStmtManager *stmtManager, char *query, int numberParams){
    InsertParamFinder *paramFinder = &app->model.query.paramFinder;
    MySqlTable *tables = app->model.tables;

    loadInsertParamFinder(app, paramFinder, query, numberParams);

    if (paramFinder->listBeforeWordValues == 0) {
        getParamNameByMysqlTable(app, paramFinder, stmtManager, tables);
    } else {
        getParamNameByListFieldsNames(app, paramFinder, stmtManager);
    }

    quitInsertParamFinder(paramFinder);
}


void loadInsertParamFinder(App *app, InsertParamFinder *paramFinder, char *query, int numberParams){

    char *queryWithoutWordNow = strReplace(app, query, "NOW()", '_');

    //verify if query content 'VALUES'
    paramFinder->listBeforeWordValues = (ifColumnsNamesBeforeValues(queryWithoutWordNow)) ? 1 : 0;

    if (paramFinder->listBeforeWordValues == 0){
        loadIndexAndStringsParenthesis(app, paramFinder, queryWithoutWordNow, numberParams);
    } else {
        loadIndexAndStringsAndFieldsParenthesis(app, paramFinder, queryWithoutWordNow, numberParams);
    }

    free(queryWithoutWordNow);
}

/**
*Check if columns names existe before the word "VALUES"
*
*@param (char *) query - insert query
*/
short ifColumnsNamesBeforeValues(char *query) {

    char *parenthesis;      //address where the parenthesis '(' is situated in query
    char *valuesWord;       //address where "VALUES" is situated in query
    int difference;         //difference of address of parenthesis and address of valuesWord
    short result;           //result if parenthesis is before of after "VALUES"

    parenthesis = strchr(query, '(');
    valuesWord = strstr(query, "VALUES");
    difference = parenthesis - valuesWord;
    result = (difference < 0) ? 1 : 0;

    return result;
}

/**
*Load structure InsertParamFinder if specific columns names are indicated in insert query
*
*@param (App *) app - structure of application
*@param (InsertParamFinder *) paramFinder - structure to get fields of parameters in insert query
*@param (char *) query - insert query
*@param (int) numberParams - number of parameters in insert prepared query
*/
void loadIndexAndStringsParenthesis(App *app, InsertParamFinder *paramFinder, char *query, int numberParams){

    char *temp = getStrBtw2rChr(app, query, '(', ')', 0); // get string in parenthesis

    getListStringAndNumberFields(app, &paramFinder->listContentParenthesis, temp, ',', &paramFinder->numberFields);

    searchAndGetIndexWhereQMark(app, paramFinder, numberParams);

    free(temp);
}


void searchAndGetIndexWhereQMark(App *app, InsertParamFinder *paramFinder, int numberParams) {
    int i = 0;
    int j;

    paramFinder->indexsOfQParenthesis = malloc(sizeof(int) * numberParams);
    verifyPointer(app, paramFinder->indexsOfQParenthesis, "Problem malloc in paramFinder->indexsOfQParenthesis");

    for (j = 0; j < paramFinder->numberFields; j++) {
        if(strchr(paramFinder->listContentParenthesis[j], '?') != NULL) {
            paramFinder->indexsOfQParenthesis[i] = j;
            i++;
        }
    }
}

void getParamNameByMysqlTable(App *app, InsertParamFinder *paramFinder, MySqlStmtManager *stmtManager, MySqlTable *tables) {
    int i;
    int j;
    int concernIndex;
    Varchar table;

    strcpy(table, stmtManager->tablesNames[0]);

    for (i = 0; i < app->model.numberAllTables; i++) {

        if(strncmp(tables[i].tableName, table, strlen(table) + 1) == 0) {

            if (paramFinder->numberFields == tables[i].numberField){

                stmtManager->paramsNames = malloc(sizeof(Varchar) * tables[i].numberField);
                verifyPointer(app, stmtManager->paramsNames, "Problem malloc stmtManager->paramsNames in fillListFieldByMysqlTables");

                for (j = 0; j < stmtManager->numberParams; j++) {
                    concernIndex = paramFinder->indexsOfQParenthesis[j];
                    strcpy(stmtManager->paramsNames[j], tables[i].listFieldsNames[concernIndex]);
                }
            } else {
                printf("Error[modelParamFinder] : paramFinder->numberFields and table[%d].numberField are not equal", i);
                quitApp(app);
            }
        }
    }
}

void loadIndexAndStringsAndFieldsParenthesis(App *app, InsertParamFinder *paramFinder, char *query, int numberParams){
    char *strFieldsNames = getStrBtw2Chr(app, query, '(', ')', 0);
    char *strValues = getStrBtw2rChr(app, query, '(', ')', 0);

    getListStringAndNumberFields(app, &paramFinder->listContentParenthesis, strValues, ',', &paramFinder->numberFields);

    getListStringAndNumberFields(app, &paramFinder->listFieldsParenthesis, strFieldsNames, ',', NULL);

    removeSpacesToEachVarcharInList(app, paramFinder->listFieldsParenthesis, paramFinder->numberFields);

    searchAndGetIndexWhereQMark(app, paramFinder, numberParams);

    free(strFieldsNames);
    free(strValues);
}

void removeSpacesToEachVarcharInList(App *app, Varchar *listVarchar, int numberFields) {
    int i;
    char *addressSpace;
    int length;
    Varchar temp;

    for (i = 0; i < numberFields; i++) {

       while(strchr(listVarchar[i], ' ') != NULL) {
            addressSpace = strchr(listVarchar[i], ' ');
            if (addressSpace != NULL) {

                if (strncmp(listVarchar[i], addressSpace, strlen(listVarchar[i] + 1)) == 0) {
                    strcpy(temp, listVarchar[i]);
                    strcpy(listVarchar[i], temp + 1);
                } else if (listVarchar[i][strlen(listVarchar[i]) - 1] == ' '){
                    length = strlen(listVarchar[i]) - 1;
                    listVarchar[i][length] = '\0';
                } else {
                    printf("Error : Field's name of param content space. It's forbidden\n");
                    quitApp(app);
                }
            }
        }
    }
}

void getParamNameByListFieldsNames(App *app, InsertParamFinder *paramFinder, MySqlStmtManager *stmtManager) {

    int i;
    int concernIndex;

    stmtManager->paramsNames = malloc(sizeof(Varchar) * stmtManager->numberParams);
    for (i = 0; i < stmtManager->numberParams; i++) {

        concernIndex = paramFinder->indexsOfQParenthesis[i];
        strcpy(stmtManager->paramsNames[i], paramFinder->listFieldsParenthesis[concernIndex]);
    }
}

char *strReplace(App *app, char *stringToCheck, char *strRemove, char charReplace) {
    int i;
    int start;
    char *result = malloc(sizeof(char) * (strlen(stringToCheck) + 1));
    verifyPointer(app, result, "Problem malloc of result in strReplace\n");
    strcpy(result, stringToCheck);

    while(strstr(result, strRemove) != NULL) {
        start = strstr(result, strRemove) - result;
        for (i = 0; i < strlen(strRemove); i++) {
            result[start + i] = charReplace;
        }
    }

    return result;
}

/**
*function to sub string between first and last char in last occurrence if there are 2 same char
*
*@param (App *) app - structure of application
*@param (char *) stringToCheck - string that will be sub
*@param (char) firstChar - the first char of new string, target with strrchr
*@param (char) lastChar - the last char of new string, target with strrchr
*@param (short) includeChars - if includeChars == 1, firstChar and lastChar are include in new string, otherwise they are exclude
*/
char *getStrBtw2rChr(App *app, char *stringToCheck, char firstChar, char lastChar, short includeChars) {
    int min;
    int max;
    char *indexString;
    char *result;


    if (firstChar != 0){
        indexString = strrchr(stringToCheck, firstChar);
        verifyPointer(app, indexString, "Problem for strrchr indexString in loadInsertParamFinder");
        min = indexString - stringToCheck + ((includeChars) ? 0 : 1);
    } else {
        min = 0;
    }


    if (lastChar != 0) {
        indexString = strrchr(stringToCheck, lastChar);
        verifyPointer(app, indexString, "Problem for strrchr indexString in loadInsertParamFinder");
        max = indexString - stringToCheck + ((includeChars) ? 1 : 0);
    } else {
        max = strlen(stringToCheck);
    }

    result = mySubString(app, stringToCheck, min, max);

    return result;
}

/**
*function to sub string between first and last char in first occurrence if there are 2 same char
*
*@param (App *) app - structure of application
*@param (char *) stringToCheck - string that will be sub
*@param (char) firstChar - the first char of new string, target with strchr
*@param (char) lastChar - the last char of new string, target with strchr
*@param (short) includeChars - if includeChars == 1, firstChar and lastChar are include in new string, otherwise they are exclude
*/
char *getStrBtw2Chr(App *app, char *stringToCheck, char firstChar, char lastChar, short includeChars) {
    int min;
    int max;
    char *indexString;
    char *result;

    if (firstChar != 0){
        indexString = strchr(stringToCheck, firstChar);
        verifyPointer(app, indexString, "Problem for strchr indexString in loadInsertParamFinder");
        min = indexString - stringToCheck + ((includeChars) ? 0 : 1);
    } else {
        min = 0;
    }

    if (lastChar != 0) {
        indexString = strchr(stringToCheck, lastChar);
        verifyPointer(app, indexString, "Problem for strchr indexString in loadInsertParamFinder");
        max = indexString - stringToCheck + ((includeChars) ? 1 : 0);
    } else {
        max = strlen(stringToCheck);
    }
    result = mySubString(app, stringToCheck, min, max);

    return result;
}

char *mySubString(App *app, char *currentString, int minIndex, int maxIndex){

    char temp[100];
    char *result = malloc(sizeof(char) * (maxIndex - minIndex + 1));
    verifyPointer(app, result, "Problem malloc with result in mySubString\n");

    strcpy(temp, currentString + minIndex);
    strncpy(result, temp, maxIndex - minIndex);
    result[maxIndex - minIndex] = '\0';

    return result;
}

void getParamsNamesSelectUpdateDelete(App *app, MySqlStmtManager  *stmtManager, char *query, int numberParams){
    char temp1[MAX_TEXT];
    char temp2[MAX_TEXT];
    int max = -1, min = -1;
    Varchar name;
    int currentLenght = 0;
    int i;

    strcpy(temp1, query);
    for (i = 0; i < numberParams; i++) {
        //Chercher la premiere occurence contenant comme char '?'
        strncpy(temp2, temp1, strchr(temp1, '?') - temp1);

        //obtenir du debut a la premiere occurence '?' pour trouver son parametre
        temp2[strchr(temp1, '?') - temp1] = '\0';

        getBeginAndEndOfParamName(temp2, &min, &max);

        mySubVarchar(name, temp2, min, max);
        addStringInList(app, name, &stmtManager->paramsNames, &currentLenght);

        //Enlever la premiere occurence '?' et initialisez max et min
        temp1[strchr(temp1, '?') - temp1] = '_';
        max = -1;
        min = -1;
    }
}

void getBeginAndEndOfParamName(char *query, int *min, int *max) {
    int length = strlen(query);

    while (length >= 0 && (*max < 0 || *min < 0)) {

        //trouver la derniere lettre du parametre
        if (query[strlen(query) - 1] != '=' && query[strlen(query) - 1] != ' ') {
            *max = strlen(query);
        }

        // trouver la premiere lettre du parametre apres avoir trouver la derniere
        if (*max != -1){
            if (strrchr(query, ' ')){
                *min = strrchr(query, ' ') - query + 1;
                break;
            } else {
                printf("Warning : Problem of query instruction.\n");
            }
        }
        //s'il n'y a pas de *max et de *min, reduire la chaine en enlevant le dernier charactere
        query[strlen(query) - 1] = '\0';
        length = strlen(query);

        if (length == 0){
            printf("Warning : This query is not prepared\n");
            break;
        }
    }
}


void mySubVarchar(Varchar newString, const char* stringToSub, int minIndex, int maxIndex) {
    int length = maxIndex - minIndex + 1;

    strncpy(newString, stringToSub + minIndex, length);
    *(newString + length) = '\0';
}

void getListStringAndNumberFields(App *app, Varchar **listFields, char *strToSplit, char delimiter, int *numberFields) {
    char *indexDelimiter;   // address that content delimiter
    Varchar strToReduce;    // string that it is reduced to each demiliter found
    Varchar strInElement;   // string between the begin of strToReduce  and delimiter
    int currentNumber = 0;

    strcpy(strToReduce, strToSplit);
    while(1){

        indexDelimiter = strchr(strToReduce, delimiter);

        strncpy(strInElement, (const char*)strToReduce, indexDelimiter - strToReduce + 1);
        strInElement[indexDelimiter - strToReduce] = '\0';

        addStringInList(app, strInElement, listFields, (numberFields == NULL) ? &currentNumber : numberFields);

        strcpy(strToReduce, indexDelimiter + 1);

        if (strchr(strToReduce, delimiter) == NULL){
            addStringInList(app, strToReduce, listFields, (numberFields == NULL) ? &currentNumber : numberFields);
            break;
        }
    }
}

void addStringInList(App *app, Varchar paramName, Varchar **listString, int *currentLength) {
    Varchar *inter;
    int length = *currentLength;
    int i;

    if ((*listString) == NULL) {
        inter = malloc(sizeof(Varchar));
        verifyPointer(app, inter, "Problem malloc inter in addStringInList\n");
    } else {
        inter = malloc(sizeof(Varchar) * (length + 1));
        verifyPointer(app, inter, "Problem malloc inter in addStringInList\n");
        for (i = 0; i < length; i++) {
            strcpy(inter[i], (*listString)[i]);
        }
    }

    strcpy(inter[length], paramName);
    (*currentLength)++;

    if ((*listString) != NULL){
        free(*listString);
    }
    (*listString) = inter;
}
