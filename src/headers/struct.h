#ifndef _STRUCTURE
#define _STRUCTURE

#include <SDL2/SDL.h>
#include <mysql.h>
#define WINDOW_POS_X    200
#define WINDOW_POS_Y    100


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

typedef struct App {
    SDL_Window *screen;
    SDL_Renderer *renderer;
    Colors colors;
    Config config;
    MYSQL mysql;
} App;
#endif // _STRUCTURE
