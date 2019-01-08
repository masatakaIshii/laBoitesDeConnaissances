
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <mysql.h>
#include "../headers/common.h"
#include "../headers/play.h"
#include "../headers/model/modelHelper/modelInit.h"
#include "../headers/model/modelHelper/modelQuit.h"

int mainEventLoop(App *app) {
    SDL_Event event;
    int done = 0;

    while (!done) {
        SDL_WaitEvent(&event);
        switch (event.type){
            // Quitte le programme
            case SDL_QUIT:
                return EXIT_SUCCESS;

            // Redimensionnement de la fenetre
            case SDL_WINDOWEVENT:
                if(event.window.event == SDL_WINDOWEVENT_RESIZED)
                    resizeScreen(app, event.window.data2);
            break;

            case SDL_KEYDOWN:
                // Quitte le programme
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                    return EXIT_SUCCESS;
                // MODE PLAY
                if (event.key.keysym.scancode == SDL_SCANCODE_1)
                    playMode(app);
                // MODE CREATE
                if (event.key.keysym.scancode == SDL_SCANCODE_2)
                    // Fonction CREATE
            break;
        }
        displayMenu(app);
    }

    return 2;
}

void displayMenu(App *app) {
    // On set la couleur du fond d'ecran
    SDL_SetRenderDrawColor(app->renderer, app->colors.blue[0], app->colors.blue[1], app->colors.blue[2], app->colors.blue[3]);
    SDL_RenderClear(app->renderer);
    // On creer le boutton Play
    createRect(app, app->config.width / 3, app->config.height / 1.5, app->config.width / 12, app->config.height / 4, app->colors.green);
    // On creer le boutton Create
    createRect(app, app->config.width / 3, app->config.height / 1.5, (app->config.width / 12) * 7, app->config.height / 4, app->colors.yellow);
    // Actualisation de l'ecran
    SDL_RenderPresent(app->renderer);
}

void resizeScreen(App *app, int height) {
    // On charge la nouvelle config
    //loadConfig(&(app->config));

    // On redimensionne la fenï¿½tre
    SDL_SetWindowSize(app->screen, app->config.width, app->config.height);
}

void createRect(App *app, int width, int height, int x, int y, Uint8* color) {
    // Definition du rectangle
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;

    // Definition de la couleur
    SDL_SetRenderDrawColor(app->renderer, color[0], color[1], color[2], color[3]);

    // Creation du rectangle en couleur
    SDL_RenderFillRect(app->renderer, &rect);
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
        // On ferme la SDL et on sort du programme
        printf("%s\n", message);
        quitApp(app);
        exit(EXIT_FAILURE);
    }
}

void loadConfig(Config *config) {
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
        strcpy(value, ptr + 1);
        strncpy(param, line, ptr - line);
        param[ptr-line] = '\0';

        if(strcmp(param, "windowHeight") == 0){
            config->height = (int)strtol(value, NULL, 0);
            config->width = config->height * 1.95; // Largeur intialise au format 16/9 suivant la hauteur
        }
        //else if(strcmp(param, "color1") == 0)
            // Set la couleur ici
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
    loadConfig(&config);
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

    // Connexion à la base de données , initialisation et chargement

    InitModel(&app->model);

    dbConnect(app);

    loadFileModelTables(app);
}

void quitApp(App *app){
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->screen);
    SDL_Quit();

    quitModel(&app->model);
}
