#include <SDL2/SDL.h>

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
} App;
