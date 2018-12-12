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

    // Start SDL
    freopen("CON", "w", stdout);
    freopen("CON", "r", stdin);
    freopen("CON", "w", stderr);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Unable to init SDL: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    loadApp(&app);

    returnStat = mainEventLoop(&app);
    /*mysql test*/
    unsigned int numberFields;
    unsigned int numberRows;
    unsigned int typeField = 9;
    unsigned int *listFieldTypes;
    unsigned int test;


    char ***resultQuery = querySelect(&app, "SELECT * FROM user", &numberFields, &numberRows);

    char **resultFieldsInfo = getFieldsName(&app, "user", &numberFields, NULL);

    showQueryResult(&resultQuery, &numberFields, &numberRows, resultFieldsInfo);

    freeResultStringTable(&resultQuery, numberFields, numberRows);
    freeFieldsList(&resultFieldsInfo, numberFields);

    test = getProperFieldAndTable(&app, "user.name", NULL);

    quitApp(&app);

    return returnStat;
}
