#ifndef _STRUCTURE
#define _STRUCTURE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <winsock2.h>
#include <mysql.h>
#define WINDOW_POS_X    200
#define WINDOW_POS_Y    100
#define MAX_VARCHAR 255
#define MAX_TEXT 1000
#define free(ptr) free(ptr), ptr=NULL

typedef struct Colors {
    Uint8 blue[4];
    Uint8 lightblue[4];
    Uint8 green[4];
    Uint8 yellow[4];
} Colors;

typedef struct Config {
    int width;
    int height;
} Config;

/* Model */

typedef char Varchar[MAX_VARCHAR];
typedef char Text[MAX_TEXT];
/**
*@struct MySqlTable : pour avoir les informations d'une table, nécessaire lors d'une requête préparée
*@var (char) tableName : le nom de la table dans une base de données
*@var (char **) listFieldsNames : la liste des champs de la table
*@var (int) numberField : le nombre de champs de la table
*@var (unsigned int *) listFieldsTypes : la liste des type MYSQL_TYPE_ correspondant chaque index au nom du champ concerné
*/
typedef struct MySqlTable {
    Varchar tableName;
    Varchar *listFieldsNames;
    int numberField;
    unsigned int *listFieldsTypes;
} MySqlTable;

/* Query to the database*/
//Les structures pour la partie bind
typedef struct MySqlParamsBind {
    int paramsTypes;
    char *paramsString;
    int paramsStrLen;
    int paramNumber;
    double paramDouble;
    MYSQL_TIME paramsDateTime;
    int paramsIsNull;
    unsigned long paramsLengths;
} MySqlParamsBind;

typedef struct MySqlStmtManager {
    MYSQL_STMT *stmt;
    short ifStmtIsInit;
    char *currentQuery;
    Varchar *tablesNames;
    int numberTables;
    Varchar *paramsNames;
    int numberParams;
    MySqlParamsBind *params;
    MYSQL_BIND *buffersBind;
} MySqlStmtManager;

// Concernant les requêtes préparées
/**
*@struct SelectQuery : to get informations of select query
*
*@var (MYSQ_RES) - *result : mysql data structure that content result's informations of select query
*@var (char ***) - listColumnsRows : list of columns and rows correspond of result of query
*@var (Varchar *) - listFields : list of fields names of query
*@var (unsigned int) - numberFields : number of fields of the query select's result
*@var (unsigned int) - numberRows : number of rows of query select's result
*@var (short) - resultWithFieldsList : bool if listColumnsRows content list of fields
*/
typedef struct SelectQuery {
    MYSQL_RES *result;
    char ***listColumnsRows;
    Varchar *listFields;
    unsigned int numberFields;
    unsigned int numberRows;
    short resultWithFieldsList;
} SelectQuery;

typedef struct Query {
    MySqlStmtManager stmtManager;
    SelectQuery selectQuery;
} Query;

typedef struct Model {
    MYSQL *mysql;
    short ifMysqlIsInit;
    MySqlTable *tables;
    Varchar *listAllTables;
    int numberAllTables;
    Query query;
} Model;

/**
*@struct InsertParamFinder : to help to get fields of params values
*@var (Varchar*) listFieldsParenthesis : list of content ? or values in specific parenthesis
*@var (short) - listBeforeWordValues : bool if there are list of fields in parenthesis before word "VALUES"
*@var (int) - numberFields : number of fields of columns that is specifies in insert query
*@var (int*) - indexsOfQParenthesis : list of index corredpond to the ? marks placements
*@var (Varchar*) listFieldsParenthesis : list of fields in specific parenthesis
*/
typedef struct InsertParamFinder{
    Varchar *listContentParenthesis;
    short listBeforeWordValues;
    int numberFields;
    int *indexsOfQParenthesis;
    Varchar *listFieldsParenthesis;

}InsertParamFinder;

/* --App-- */
typedef struct App {
    SDL_Window *screen;
    SDL_Renderer *renderer;
    Colors colors;
    Config config;
    Model model;
} App;



#endif // _STRUCTURE
