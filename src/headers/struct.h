#ifndef _STRUCTURE
#define _STRUCTURE

#include <SDL2/SDL.h>
#include <winsock2.h>
#include <mysql.h>
#define BPP     32
#define WINDOW_POS_X    200
#define WINDOW_POS_Y    100
#define MAX_VARCHAR 100


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
/**
*@struct MySqlTable : pour avoir les informations d'une table, nécessaire lors d'une requête préparée
*@var (char) tableName : le nom de la table dans une base de données
*@var (char **) listFieldsNames : la liste des champs de la table
*@var (int) numberField : le nombre de champs de la table
*@var (unsigned int *) listFieldsTypes : la liste des type MYSQL_TYPE_ correspondant chaque index au nom du champ concerné
*/
typedef struct MySqlTable {
    char tableName[MAX_VARCHAR];
    char **listFieldsNames;
    int numberField;
    unsigned int *listFieldsTypes;
} MySqlTable;

/* Query to the database*/
//Les structures pour la partie bind
typedef struct MySqlParamsBind {
    int paramsTypes;
    int paramsBufferLengths;
    char *paramsBuffer;
    int paramsIsNull;
    int paramsLengths;
    MYSQL_TIME datetimeBind;
    int paramsDateTime;
} MySqlParamsBind;

typedef struct MySqlStmtManager {
    MYSQL_STMT *stmt;
    MYSQL_BIND *buffersBind;
    int numberTables;
    MySqlParamsBind *params;
    int numberParams;
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
    char **listFields;
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
    MySqlTable *tables;
    char **listAllTables;
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
