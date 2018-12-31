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

    /*mysql test*/
//    char * query = "SELECT box.name, list.name, list.description FROM box, list WHERE list.id = 1 AND box.id = 1";
//
//    getSelectQuery(&app, query);
//
//    addFieldsToResult(&app); //@TODO : trouver bug dans cette fonction
//
//    removeFieldsInResult(&app);
//
//    addFieldsToResult(&app);
//
//    showQueryResult(&app);
//
//    freeSelectQuery(&app);
//
//    int rowAffected = queryIUD(&app, "UPDATE box SET name = 'the box', modified_date = '28-12-24 00:00:00' WHERE id = 3");
//    printf("number of row affected : %d\n", rowAffected);

    char *tables[100] = {"box", "list"};
    char *paramsValues[100] = {"toto", "tata", "this is THE box", "2"};
    char *preparedQueryIUD = "UPDATE box, list SET box.name = ?, list.name = ? WHERE box.description = ? AND list.id = ?";
    int result = 0;

    setPreparedQuery(&app, preparedQueryIUD, tables, 2);

    printf("numberParams : %d\n", app.model.query.stmtManager.numberParams);
    setBindParams(&app, paramsValues);
    //result = sendPreparedQueryIUD(&app, preparedQueryIUD);


    quitApp(&app);


    return returnStat;
}
