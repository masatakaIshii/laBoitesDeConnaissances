/*
** Filename : main.c
**
** Made by  : Baptiste LEGO
**
** Description  : main function start and quit App
*/

#include <stdlib.h>
#include <stdio.h>
#include "headers/common.h"
#include "headers/play.h"
#include "headers/model/modelSelect.h"
#include "headers/model/modelShow.h"
#include "headers/model/modelIUD.h"

int main(int argc, char **argv) {
    App app;
    int returnStat;

    freopen("CON", "w", stdout);
    freopen("CON", "r", stdin);
    freopen("CON", "w", stderr);

    // Start SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Unable to init SDL: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    loadApp(&app);

    returnStat = mainEventLoop(&app);

    /*mysql test*/
 /*   unsigned int numberFields;
    unsigned int numberRows;
    char ***resultQuery = querySelect(&app, "SELECT * FROM user", &numberFields, &numberRows);
    char **resultFieldsInfo = getFieldsNameType(&app, "user", NULL);

    showQueryResult(&resultQuery, &numberFields, &numberRows, resultFieldsInfo);

    freeResultStringTable(&resultQuery, numberFields, numberRows);
*/
    quitApp(&app);

    return returnStat;
}
