#include "struct.h"

void mainEventLoop(App *app);
void displayMenu(App *app);
void resizeScreen(App *app, int height);
void createRect(SDL_Surface *screen, int width, int height, int x, int y, Uint32 color);
void verifyPointer(void *pointer, char* message);
void setPosition(SDL_Rect *position, int x, int y);
void loadColors(SDL_Surface *screen, Colors *colors);
void loadConfig(Config *config, int height);
void loadApp(App *app);
