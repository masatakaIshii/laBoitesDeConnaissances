/*
** Filename : modelParamFinder.c
**
** Made by  : Masataka ISHII
**
** Description  : get parameters of query
*/

#ifndef MODEL_PARAM_FINDER
#include "../../struct.h"
#include "../../common.h"
#include "modelCommon.h"
#include "modelInit.h"
#include "modelQuit.h"
void getParamsNames(App *app, MySqlStmtManager  *stmtManager, char *query, int numberParams);
void getParamsNamesInsert(App *app, MySqlStmtManager *stmtManager, char *query, int numberParams);

void loadInsertParamFinder(App *app, InsertParamFinder *paramFinder, char *query, int numberParams);
short ifColumnsNamesBeforeValues(char *query);

void loadIndexAndStringsParenthesis(App *app, InsertParamFinder *paramFinder, char *query, int numberParams);
void searchAndGetIndexWhereQMark(App *app, InsertParamFinder *paramFinder, int numberParams);
void getParamNameByMysqlTable(App *app, InsertParamFinder *paramFinder, MySqlStmtManager *stmtManager, MySqlTable *tables);

void loadIndexAndStringsAndFieldsParenthesis(App *app, InsertParamFinder *paramFinder, char *query, int numberParams);
void removeSpacesToEachVarcharInList(App *app, Varchar *listVarchar, int numberFields);

void getParamsNamesSelectUpdateDelete(App *app, MySqlStmtManager  *stmtManager, char *query, int numberParams);
void getBeginAndEndOfParamName(char *query, int *minIndex, int *maxIndex);
void mySubVarchar(Varchar newString, const char* stringToSub, int minIndex, int maxIndex);
void getParamNameByListFieldsNames(App *app, InsertParamFinder *paramFinder, MySqlStmtManager *stmtManager);

char *strReplace(App *app, char *stringToCheck, char *strRemove, char charReplace);
char *getStrBtw2rChr(App *app, char *stringToCheck, char firstChar, char lastChar, short includeChars);
char *getStrBtw2Chr(App *app, char *stringToCheck, char firstChar, char lastChar, short includeCharss);
char *mySubString(App *app, char *currentString, int minIndex, int maxIndex);
void getListStringAndNumberFields(App *app, Varchar **listFields, char *strToSplit, char delimiter, int *numberFields);
void addStringInList(App *app, Varchar paramName, Varchar **listString, int *currentLength);
#endif // MODEL_PARAM_FINDER
