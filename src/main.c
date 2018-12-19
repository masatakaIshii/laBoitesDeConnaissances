#include <stdlib.h>
#include <stdio.h>
#include "headers/struct.h"
#include "headers/common.h"
#include "headers/play.h"
#include "headers/model/modelCommon.h"
#include "headers/model/modelIUD.h"


#define free(ptr) free(ptr), ptr=NULL

int main(int argc, char **argv) {
    App app;

    int returnStat = NULL;

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

    //char ***resultQuery = querySelect(&app, "SELECT list.name, box.name FROM list, box WHERE list.id_box=1 AND box.id_box_parent=1", &numberFields, &numberRows);

    //char **resultFieldsInfo = getFieldsName(&app, "box", &numberFields, NULL);

    //showQueryResult(&resultQuery, &numberFields, &numberRows, NULL);
//
//    freeResultStringTable(&resultQuery, numberFields, numberRows);
    //freeFieldsList(&resultFieldsInfo, numberFields);

    char *tables[100] = {"box"};
    char *paramNames[100] = {"name", "id"};
    char *paramsValues[100] = {"notRandomBox", "2"};
    int result = 0;
    result = preparedQueryIUD(&app, "UPDATE box SET name = ? WHERE id = ?", tables, 1, paramNames, paramsValues, 2);

    printf("result : %d", result);
    quitApp(&app);

    return returnStat;
}
