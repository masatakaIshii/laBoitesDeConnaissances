#include <SDL.h>

#define BPP     32

typedef struct Colors {
    Uint32 blue;
    Uint32 lightblue;
    Uint32 green;
    Uint32 yellow;
} Colors;

typedef struct Config {
    int width;
    int height;
} Config;
