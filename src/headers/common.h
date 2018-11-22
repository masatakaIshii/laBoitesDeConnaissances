#include "struct.h"

void mainEventLoop(SDL_Surface* screen, Config *config);
void displayMenu(SDL_Surface *screen, Config *config, Colors *colors);
void resizeScreen(SDL_Surface *screen, Config *config, int height);
void createRect(SDL_Surface *screen, int width, int height, int x, int y, Uint32 color);
void verifyPointer(void *pointer, char* message);
void setPosition(SDL_Rect *position, int x, int y);
void loadColors(SDL_Surface *screen, Colors *colors);
void loadConfig(Config *config, int height);
