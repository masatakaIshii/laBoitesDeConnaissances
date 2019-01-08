#include "headers/struct.h"
#include "headers/common.h"
#include "headers/play.h"
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

int main(int argc, char **argv) {

    App app;
    MYSQL mysqlFirst;
    app.model.mysql = &mysqlFirst;

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

    quitApp(&app);

    return returnStat;
}
