/*
** Filename : main.c
**
** Made by  : Baptiste LEGO
**
** Description  : main function start and quit App
*/

#include <stdlib.h>
#include <stdio.h>
#include "headers/struct.h"
#include "headers/common.h"
#include "headers/menu.h"
#include "headers/model/modelHelper/modelCommon.h"
#include "headers/model/modelHelper/modelQuit.h"
#include "headers/model/modelHelper/modelSelect.h"
#include "headers/model/modelHelper/modelShow.h"
#include "headers/model/modelHelper/modelIUD.h"
#include "headers/model/modelHelper/modelBindHelper.h"
#include "headers/model/modelHelper/modelStmtManager.h"
#include "headers/model/modelHelper/modelBindHelper.h"
#include "headers/model/modelHelper/modelParamFinder.h"
#include "headers/model/modelHelper/modelFetchSelectHelper.h"
#include "headers/play/box.h"
#include "headers/controll/create.h"
#include "headers/controll/createList.h"
#include "headers/view/commonView.h"
#include "headers/view/create/createViewBoxes.h"
#include "headers/controll/form.h"

int main(int argc, char **argv) {

    App app;
    MYSQL mysqlFirst;
    app.model.mysql = &mysqlFirst;

    int returnStat = NULL;

    freopen("CON", "w", stdout);
    freopen("CON", "r", stdin);
    freopen("CON", "w", stderr);

    // Start SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Unable to init SDL: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    // Start SDL_Ttf
    if(TTF_Init() < 0) {
        fprintf(stderr, "Unable to init SDL_ttf: %s\n", TTF_GetError());
        return EXIT_FAILURE;
    }

    loadApp(&app);

    returnStat = mainEventLoop(&app);

    quitApp(&app);

    return returnStat;
}
