#include <stdlib.h>
#include <stdio.h>
#include "headers/common.h"
#include "headers/play.h"
#include "headers/model/modelSelect.h"
#include "headers/model/modelShow.h"

int main(int argc, char **argv) {
    App app;
    dbConnect(&app.mysql);
    // Start SDL
    freopen("CON", "w", stdout);
    freopen("CON", "r", stdin);
    freopen("CON", "w", stderr);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Unable to init SDL: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_WM_SetIcon(SDL_LoadBMP("img/icon.bmp"), NULL); // Chargement de l'icone du programme
    SDL_WM_SetCaption(".::. The box of knowledge .::.", NULL); // Chargement du nom du programme

    loadApp(&app);

    mainEventLoop(&app);

    SDL_Quit();

    /*mysql test*/
    unsigned int numberFields;
    unsigned int numberRows;

    char *** resultQuery = querySelect(&app.mysql, "SELECT * FROM user", &numberFields, &numberRows, 0);
    char **resultFieldsInfo = getFieldsNameType(&app.mysql, "user", NULL);

    showQueryResult(&resultQuery, &numberFields, &numberRows, resultFieldsInfo);

    freeResultStringTable(&resultQuery, numberFields, numberRows);

    freeFieldsList(&resultFieldsInfo, numberFields);


    return EXIT_SUCCESS;
}
