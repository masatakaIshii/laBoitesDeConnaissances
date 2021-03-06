/*
** Filename : common.c
**
** Made by  : Baptiste LEGO, Masataka ISHII
**
** Description  : common functions used in App
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <mysql.h>
#include "../headers/common.h"
#include "../headers/model/modelHelper/modelInit.h"
#include "../headers/model/modelHelper/modelQuit.h"

void commonEvents(App *app, SDL_Event event, int *done){
    // Quit the program
    if(event.type == SDL_QUIT){
        quitApp(app);
        exit(EXIT_SUCCESS);
    }

    // Back
    if(event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
        *done = 1;

    // Resize screen
    if(event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED)
        resizeScreen(app, event.window.data2);
}

void resizeScreen(App *app, int height) {
    // Load new config
    app->config.height = height;
    app->config.width = height * SCREEN_FORMAT;

    // Resize window
    SDL_SetWindowSize(app->screen, app->config.width, app->config.height);
}

int hRatio9(App *app, double ratioHeight) {
    return round(ratioHeight * (double)app->config.height / 9);
}

int wRatio16(App *app, double ratioWidth) {
    return round(ratioWidth * (double)app->config.width / 16);
}

SDL_Rect createRect(App *app, int width, int height, int x, int y, Uint8* color) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;

    // Color
    SDL_SetRenderDrawColor(app->renderer, color[0], color[1], color[2], color[3]);

    // Create rect with color
    SDL_RenderFillRect(app->renderer, &rect);

    return rect;
}

int inRect(SDL_Rect rect, int clicX, int clicY){
    int x, y;

    for(x = 0; x < rect.w; x++){
        for(y = 0; y < rect.h; y++){
            if(x + rect.x == clicX && y + rect.y == clicY){
                return 1;
            }
        }
    }

    return 0;
}

SDL_Texture *textToTexture(App *app, char *pathFontFile, char *text, int fontSize, typeRenderText typeRender, SDL_Color colorFg) {
    SDL_Texture *textTexture = NULL;
    SDL_Surface *textSurface = NULL;
    TTF_Font *font = NULL;

    font = TTF_OpenFont(pathFontFile, fontSize);
    verifyPointer(app, font, "Problem font\n");

    if (typeRender == TEXT_SOLID){
        textSurface = TTF_RenderUTF8_Solid(font, text, colorFg);
        verifyPointer(app, textSurface, "Problem textSurface to render text_solid\n");
    }
    if (typeRender == TEXT_BLENDED) {
        textSurface = TTF_RenderUTF8_Blended(font, text, colorFg);
        verifyPointer(app, textSurface, "Problem textSurface to render text_blended\n");
    }


    textTexture = SDL_CreateTextureFromSurface(app->renderer, textSurface);
    verifyPointer(app, textTexture, "Problem textTexture\n");

    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);

    return textTexture;
}

void renderText(App *app, SDL_Rect rect, char *pathFontFile, char *text, int fontSize, typeRenderText typeRender, SDL_Color textColor){

    if (strlen(text) == 0){
        return;
    }
    SDL_Texture *textTexture = textToTexture(app, pathFontFile, text, fontSize, typeRender, textColor);

    SDL_RenderCopy(app->renderer, textTexture, NULL, &rect);

    SDL_DestroyTexture(textTexture);
}

void writeTitle(App *app, char *title){
    SDL_Rect textPos;

    // Write title
    textPos.h = hRatio9(app, 1.5);
    textPos.y = 0;

    if(strlen(title) < 6){
        textPos.w = wRatio16(app, 2);
        textPos.x = wRatio16(app, 7);
    }
    else if(strlen(title) < 12){
        textPos.w = wRatio16(app, 4);
        textPos.x = wRatio16(app, 6);
    }
    else{
        textPos.w = wRatio16(app, 6);
        textPos.x = wRatio16(app, 5);
    }

    renderText(app, textPos, app->config.fontCambriab, title, 80, TEXT_BLENDED, app->colors.white);
}

void writeReturnKey(App *app){
    SDL_Rect textPos;

    textPos.x = wRatio16(app, 11);
    textPos.y = 0;
    textPos.w = wRatio16(app, 5);
    textPos.h = hRatio9(app, 0.3);

    renderText(app, textPos, app->config.fontCambriab, "Appuyez sur ESC pour retourner en arriere", 40, TEXT_BLENDED, app->colors.white);
}

Uint8 *hexToRgb(const char *hex){
    char hexNumber[2];
    Uint8 *rgb = NULL;
    int i;

    rgb = malloc(sizeof(Uint8) * 4);
    if(rgb == NULL){
        printf("Unable to convert hex\n");
        return NULL;
    }

    for(i = 0; i < 3; i++){
        strncpy(hexNumber, hex, 2);
        rgb[i] = hexToDecimal(hexNumber, 2);
        hex += 2;
    }

    rgb[3] = 0;

    return rgb;
}

int hexToDecimal(char *input, int size){
    int result = 0;
    int factor = 1;
    int i;

    for(i = size - 1; i >= 0; i--){
        if(input[i] >= '0' && input[i] <= '9'){
            result += (input[i] - '0') * factor;
            factor *= 16;
        }
        else if(input[i] >= 'A' && input[i] <= 'F'){
            result += (input[i] - 'A' + 10) * factor;
            factor *= 16;
        }
        else if(input[i] >= 'a' && input[i] <= 'f'){
            result += (input[i] - 'a' + 10) * factor;
            factor *= 16;
        }
    }

    return result;
}

int intConvertor(const char* str){
    return (int)strtol(str, NULL, 0);
}

void verifyPointer(App *app, void *pointer, const char *message) {
    if (!pointer) {
        printf("%s\n", message);
        quitApp(app);
        exit(EXIT_FAILURE);
    }
}

void loadDefaultConfig(Config *config){
    config->height = 480;
    config->width = config->height * SCREEN_FORMAT;
}

void loadConfigFile(Config *config) {
    char *ptr = NULL;
    char line[200];
    char param[200];
    char value[200];

    FILE *file = fopen("config.txt", "r");
    if(file == NULL) {
        printf("Unable to load file");
    }

    while(fgets(line, 200, file) != NULL) {
        ptr = strchr(line, '=');
        if(ptr != NULL){
            strcpy(value, ptr + 1);
            value[strlen(value) - 1] = '\0';
            strncpy(param, line, ptr - line);
            param[ptr-line] = '\0';

            loadConfigParam(config, param, value);
        }
    }

    fclose(file);
}

void loadConfigParam(Config *config, char *param, char *value) {

    if(strcmp(param, "windowHeight") == 0){
        config->height = intConvertor(value);
        config->width = config->height * SCREEN_FORMAT;
    }
    (strcmp(param, "host") == 0) ? strcpy(config->host, value) : "";
    (strcmp(param, "user") == 0) ? strcpy(config->user, value) : "";
    (strcmp(param, "password") == 0) ? strcpy(config->password, value) : "";
    (strcmp(param, "database") == 0) ? strcpy(config->database, value) : "";
    (strcmp(param, "fontCambriab") == 0) ? strcpy(config->fontCambriab, value) : "";
    (strcmp(param, "fontSixty") == 0) ? strcpy(config->fontSixty, value) : "";
    (strcmp(param, "fontTimes") == 0) ? strcpy(config->fontTimes, value) : "";
}

void loadColors(Colors *colors) {
    colors->blue[0] = 93;   // RED
    colors->blue[1] = 97;   // GREEN
    colors->blue[2] = 203;  // BLUE
    colors->blue[3] = 0;    // ALPHA

    colors->green[0] = 86;
    colors->green[1] = 197;
    colors->green[2] = 138;
    colors->green[3] = 0;

    colors->yellow[0] = 191;
    colors->yellow[1] = 187;
    colors->yellow[2] = 80;
    colors->yellow[3] = 0;

    colors->lightblue[0] = 110;
    colors->lightblue[1] = 255;
    colors->lightblue[2] = 255;
    colors->lightblue[3] = 0;

    colors->pink[0] = 255;
    colors->pink[1] = 153;
    colors->pink[2] = 153;
    colors->pink[3] = 0;

    colors->red[0] = 255;
    colors->red[1] = 70;
    colors->red[2] = 70;
    colors->red[3] = 0;

    colors->black.r = 0;
    colors->black.g = 0;
    colors->black.b = 0;

    colors->white.r = 255;
    colors->white.g = 255;
    colors->white.b = 255;
}

void loadApp(App *app) {
    // Load config
    Config config;
    loadDefaultConfig(&config);
    loadConfigFile(&config);
    app->config = config;

    // Create the window
    app->screen = SDL_CreateWindow(".::. The box of knowledge .::.",
                        WINDOW_POS_X,
                        WINDOW_POS_Y,
                        app->config.width, app->config.height,
                        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    verifyPointer(app, app->screen, "Unable to set video mode");
    SDL_SetWindowIcon(app->screen, SDL_LoadBMP("img/icon.bmp"));

    // Create renderer
    app->renderer = SDL_CreateRenderer(app->screen, -1, SDL_RENDERER_ACCELERATED);
    verifyPointer(app, app->renderer, "Unable to create renderer");

    // Load colors
    Colors colors;
    loadColors(&colors);
    app->colors = colors;

    //Connection to db
    InitModel(&app->model);
    dbConnect(app);
    loadFileModelTables(app);
}

void quitApp(App *app){
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->screen);
    TTF_Quit();
    SDL_Quit();

    quitModel(&app->model);
}
