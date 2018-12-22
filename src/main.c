#include <stdlib.h>
#include <stdio.h>
#include "headers/struct.h"
#include "headers/common.h"
#include "headers/play.h"
#include "headers/model/modelSelect.h"
#include "headers/model/modelShow.h"
#include "headers/model/modelCommon.h"
#include "headers/model/modelIUD.h"


#define free(ptr) free(ptr), ptr=NULL

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
//    char * query = "SELECT * FROM list";
//    SelectQuery *selectQuery = &app.model.query.selectQuery;
    //get structure SelectQuery

    getSelectQuery(&app, query, selectQuery);


    //char **resultFieldsInfo = getFieldsName(&app, "box", &numberFields, NULL);

//    addFieldsToResult(&selectQuery->listColumnsRows, &selectQuery->listFields, &selectQuery->numberRows);


//    showQueryResult(&app, selectQuery);
//
//    freeFieldsList(selectQuery->listFields, selectQuery->numberFields);
//    freeResultStringTable(selectQuery->listColumnsRows, selectQuery->numberFields, selectQuery->numberRows);

//    int rowAffected = queryIUD(&app, "INSERT INTO box (name, description, created_date, modified_date, id_box_parent) VALUES('theBox', 'this is THE box', NOW(), NOW(), 1)");
//    printf("number of row affected : %d\n", rowAffected);
//    char *tables[100] = {"box"};,
//    char *paramNames[100] = {"name", "id"};
//    char *paramsValues[100] = {"notRandomBox", "2"};
//    int result = 0;
    //result = preparedQueryIUD(&app, "UPDATE box, box2 SET box.name = ? WHERE box2.id = ?", tables, 1, paramNames, paramsValues, 2);


    quitApp(&app);


    return returnStat;
}
