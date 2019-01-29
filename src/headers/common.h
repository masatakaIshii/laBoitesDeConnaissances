/*
** Filename : common.h
**
** Made by  : Baptiste LEGO
**
** Description  : common functions used in App
*/

#ifndef COMMON_FUNCTIONS
#include "struct.h"

void commonEvents(App *app, SDL_Event event, int *done);

void resizeScreen(App *app, int height);
int hRatio9(App *app, double ratioHeight);
int wRatio16(App *app, double ratioWidth);

SDL_Rect createRect(App *app, int width, int height, int x, int y, Uint8* color);
int inRect(SDL_Rect rect, int clicX, int clicY);

SDL_Texture *textToTexture(App *app, char *pathFontFile, char *text, int fontSize, typeRenderText typeRender, SDL_Color colorFg);
void renderText(App *app, SDL_Rect rect, char *pathFontFile, char *text, int fontSize, typeRenderText typeRender, SDL_Color textColor);
void writeTitle(App *app, char *title);

Uint8 *hexToRgb(const char *hex);
int hexToDecimal(char *input, int size);

void verifyPointer(App *app, void *pointer,const char* message);

void loadDefaultConfig(Config *config);
void loadConfigFile(Config *config);
void loadConfigParam(Config *config, char *param, char *value);
void loadColors(Colors *colors);
void loadApp(App *app);

void quitApp(App *app);
#endif // COMMON_FUNCTIONS

