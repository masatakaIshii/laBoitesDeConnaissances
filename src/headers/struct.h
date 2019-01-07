#ifndef _STRUCTURE
#define _STRUCTURE

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <mysql.h>

#define WINDOW_POS_X    200
#define WINDOW_POS_Y    100
#define SCREEN_FORMAT   1.95


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
    MYSQL mysql;
    Colors colors;
    Config config;
} App;
#endif // _STRUCTURE
