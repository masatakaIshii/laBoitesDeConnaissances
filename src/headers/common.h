/*
** Filename : common.h
**
** Made by  : Baptiste LEGO
**
** Description  : common functions used in App
*/

#ifndef COMMON_FUNCTIONS
#include "struct.h"

int mainEventLoop(App *app);
void commonEvents(App *app, SDL_Event event, int *done);
void displayMenu(App *app, SDL_Rect *buttons);
void resizeScreen(App *app, int height);
SDL_Rect createRect(App *app, int width, int height, int x, int y, Uint8* color);
int inRect(SDL_Rect rect, int clicX, int clicY);
void verifyPointer(App *app, void *pointer,const char* message);
void loadDefaultConfig(Config *config);
void loadConfigFile(Config *config);
void loadColors(Colors *colors);
void loadApp(App *app);
void quitApp(App *app);
#endif // COMMON_FUNCTIONS

