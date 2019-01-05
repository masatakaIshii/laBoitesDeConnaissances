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
    //Select query
/*
    char * query = "SELECT box.name, list.name, list.description FROM box, list WHERE list.id = 1 AND box.id = 1";
    getSelectQuery(&app, query);
    addFieldsToResult(&app);
    removeFieldsInResult(&app);
    showQueryResult(&app);
    freeSelectQuery(&app);
*/
    //process for query IUD
/*
    int rowAffected = queryIUD(&app, "UPDATE box, list SET box.name = 'toto', list.name='titi' WHERE box.id = 3 AND list.id = 1");
    printf("number of row affected : %d\n", rowAffected);
*/
    //process for prepared query IUD

    char *tables[100] = {"card"};
    char *paramsValues[100] = {"first_card", "first question ", "first answer", "2019-01-01 00:00:13"};
    char *preparedQueryIUD = "INSERT INTO card (name, question, answer, created_date) VALUES (?, ?, ?, NOW())";
//    char *paramValues[100] = {"toto", "3"};
//    char *preparedQueryIUD = "UPDATE list SET list.name = ? WHERE id = ?";
    int result = 0;

    setPreparedQuery(&app, preparedQueryIUD, tables, 1);
    //setBindParams(&app, paramsValues);

    //result = sendPreparedQueryIUD(&app, preparedQueryIUD);

    // process for prepared query select
//    char *tables[100] = {"box", "list"};
//    int numberTables = 2;
//    char *paramsValues[100] = {"1", "1"};
//    char *preparedQuerySelect = "SELECT box.name, list.name FROM box, list WHERE box.id_box_parent = ? AND list.id_box = ?";
//
//    setPreparedQuery(&app, preparedQuerySelect, tables, numberTables);
//
//    setBindParams(&app, paramsValues);
//
//    getPreparedSelectQuery(&app, preparedQuerySelect);


    quitApp(&app);

    return returnStat;
}
