#ifndef _STRUCTURE
#define _STRUCTURE

#include <SDL2/SDL.h>
#include <winsock2.h>
#include <mysql.h>
#define BPP     32
#define WINDOW_POS_X    200
#define WINDOW_POS_Y    100


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

typedef struct App {
    SDL_Window *screen;
    SDL_Renderer *renderer;
    Colors colors;
    Config config;
    MYSQL mysql;
} App;

//MySQL
typedef struct MySqlTable {
    char tableName[255];
    char **listFieldsNames;
    int numberField;
    unsigned int *listFieldsTypes;
} MySqlTable;

typedef struct MySqlParamsBind {
    int *paramsTypes;
    int *paramsBufferLengths;
    char **paramsBuffer;
    int *paramsIsNull;
    int *paramsLengths;
    MYSQL_TIME *datetimeBind;
    int *paramsDateTime;
} MySqlParamsBind;

typedef struct MySqlStmtManager {
    MYSQL_STMT *stmt;
    MYSQL_BIND *buffersBind;
    MySqlTable *tables;
    int numberTables;
    MySqlParamsBind *params;
    int numberParams;
} MySqlStmtManager;

#endif // _STRUCTURE
