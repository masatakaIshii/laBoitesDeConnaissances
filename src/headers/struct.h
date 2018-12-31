#ifndef _STRUCTURE
#define _STRUCTURE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <winsock2.h>
#include <mysql.h>
#define BPP     32
#define WINDOW_POS_X    200
#define WINDOW_POS_Y    100
#define MAX_VARCHAR 255
#define MAX_TEXT 1000
#define free(ptr) free(ptr), ptr=NULL

typedef struct Colors {
    int blue[4];
    int lightblue[4];
    int green[4];
    int yellow[4];
} Colors;

typedef struct Config {
    int width;
    int height;
} Config;

/* Model */

typedef char Varchar[MAX_VARCHAR];

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
    int paramsLengths;
} MySqlParamsBind;

typedef struct MySqlStmtManager {
    MYSQL_STMT *stmt;
    short ifStmtIsInit;
    Varchar *tablesNames;
    int numberTables;
    Varchar *paramsNames;
    int numberParams;
    MySqlParamsBind *params;
    MYSQL_BIND *buffersBind;
} MySqlStmtManager;

// Concernant les requêtes préparées
/**
*@struct SelectQuery : pour avoir les informations nécessaires après avoir effectué une requête select
*@var (char ***) listColumnsRows : liste de ligne et de colonnes correspondant au résultat de la requête select
*@var (char **) listFields : liste de champs de la requête select
*@var (int) numberFields : nombre de champs du résultat de la requête select
*@var (int) numberRows : nombre de lignes du résultat de la requête select
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

/* --App-- */
typedef struct App {
    SDL_Window *screen;
    SDL_Renderer *renderer;
    Colors colors;
    Config config;
    Model model;
} App;



#endif // _STRUCTURE
