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
void RenderMainTexts (App *app) ;

void resizeScreen(App *app, int height);
int hRatio9(App *app, double ratioHeight);
int wRatio16(App *app, double ratioWidth);

SDL_Rect createRect(App *app, int width, int height, int x, int y, Uint8* color);
SDL_Texture *textToTexture(App *app, char *pathFontFile, char *text, int fontSize, TypeRenderText typeRender, SDL_Color colorFg);
int inRect(SDL_Rect rect, int clicX, int clicY);
void verifyPointer(App *app, void *pointer,const char* message);
void loadDefaultConfig(Config *config);
void loadConfigFile(Config *config);
void loadConfigParam(Config *config, char *param, char *value);
void loadColors(Colors *colors);
void loadApp(App *app);
void quitApp(App *app);
#endif // COMMON_FUNCTIONS

