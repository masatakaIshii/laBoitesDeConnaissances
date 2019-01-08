#include "headers/struct.h"
#include "headers/common.h"
#include "headers/play.h"
#include "headers/model/modelCommon.h"
#include "headers/model/modelQuit.h"
#include "headers/model/modelSelect.h"
#include "headers/model/modelShow.h"
#include "headers/model/modelIUD.h"
#include "headers/model/modelBindHelper.h"
#include "headers/model/modelVerificator.h"
#include "headers/model/modelStmtManager.h"
#include "headers/model/modelBindHelper.h"
#include "headers/model/modelParamFinder.h"
#include "headers/model/modelFetchSelectHelper.h"

int main(int argc, char **argv) {

    App app;
    MYSQL mysqlFirst;
    app.model.mysql = &mysqlFirst;

    int returnStat = NULL;

    // Start SDL

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Unable to init SDL: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    loadApp(&app);

    returnStat = mainEventLoop(&app);

    quitApp(&app);

    return returnStat;
}
