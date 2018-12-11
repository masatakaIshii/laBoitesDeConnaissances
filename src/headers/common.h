#ifndef COMMON_FUNCTIONS
#include "struct.h"

int mainEventLoop(App *app);
void displayMenu(App *app);
void resizeScreen(App *app, int height);
void createRect(App *app, int width, int height, int x, int y, Uint8* color);
int inRect(SDL_Rect rect, int clicX, int clicY);
void verifyPointer(App *app, void *pointer, char* message);
void loadConfig(Config *config);
void loadColors(Colors *colors);
void loadApp(App *app);
void quitApp(App *app);
#endif // COMMON_FUNCTIONS

