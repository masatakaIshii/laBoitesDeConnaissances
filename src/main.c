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
    freopen("CON", "w", stdout);
    freopen("CON", "r", stdin);
    freopen("CON", "w", stderr);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Unable to init SDL: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    loadApp(&app);

    returnStat = mainEventLoop(&app);

    /* process for prepared query select*/
    char *tables2[100] = {"box", "list"};
    int numberTables = 2;
    char *paramsValues2[100] = {"1", "1"};
    char *preparedQuerySelect = "SELECT box.name, list.name FROM box, list WHERE box.id_box_parent = ? AND list.id_box = ? ORDER BY list.name";

    setPreparedQuery(&app, preparedQuerySelect, tables2, numberTables);

    setBindParams(&app, paramsValues2);

    getPreparedSelectQuery(&app, preparedQuerySelect);

    addFieldsToResult(&app);

    showQueryResult(&app);

    printf("\n");

    removeFieldsInResult(&app);

    showQueryResult(&app);

    quitPreparedSelectQuery(&app);

    quitApp(&app);

    return returnStat;
}
