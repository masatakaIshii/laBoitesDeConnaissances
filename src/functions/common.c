/*
** Filename : common.c
**
** Made by  : Baptiste LEGO
**
** Description  : common functions used in App
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <mysql.h>
#include "../headers/common.h"
#include "../headers/model/modelHelper/modelInit.h"
#include "../headers/model/modelHelper/modelQuit.h"

void commonEvents(App *app, SDL_Event event, int *done){
    // Quitte le programme
    if(event.type == SDL_QUIT){
        quitApp(app);
        exit(EXIT_SUCCESS);
    }

    // Retour
    if(event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
        *done = 1;

    // Redimensionnement de la fenetre
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

    // Utiliser sscanf(line, "%s=%s", param, value) != EOF;
    while(fgets(line, 200, file) != NULL) {
        ptr = strchr(line, '=');
        if(ptr != NULL){
            strcpy(value, ptr + 1);
            strncpy(param, line, ptr - line);
            param[ptr-line] = '\0';

            if(strcmp(param, "windowHeight") == 0){
                config->height = (int)strtol(value, NULL, 0);
                config->width = config->height * SCREEN_FORMAT; // Largeur intialise au format defini suivant la hauteur
            }
            //else if(strcmp(param, "color1") == 0)
                // Set la couleur ici
        }
    }

    fclose(file);
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
}

void loadApp(App *app) {
    // On charge la config
    Config config;
    loadDefaultConfig(&config); // Chargement d'une config par défaut si tout les parametres ne sont pas renseigner dans le fichier
    loadConfigFile(&config); //Charge le
    app->config = config;

    // On creer la fenetre
    app->screen = SDL_CreateWindow(".::. The box of knowledge .::.",
                        WINDOW_POS_X,
                        WINDOW_POS_Y,
                        app->config.width, app->config.height,
                        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    verifyPointer(app, app->screen, "Unable to set video mode");
    SDL_SetWindowIcon(app->screen, SDL_LoadBMP("img/icon.bmp")); // Chargement de l'icone du programme

    // On creer le renderer
    app->renderer = SDL_CreateRenderer(app->screen, -1, SDL_RENDERER_ACCELERATED);
    verifyPointer(app, app->renderer, "Unable to create renderer");

    // On charge les couleurs
    Colors colors;
    loadColors(&colors);
    app->colors = colors;

    // Connexion � la base de donn�es , initialisation et chargement

    InitModel(&app->model);

    dbConnect(app);

    loadFileModelTables(app);
}

void quitApp(App *app){
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->screen);
    //TTF_Quit();
    SDL_Quit();

    quitModel(&app->model);
}
