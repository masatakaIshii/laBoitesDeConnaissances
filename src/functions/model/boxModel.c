/*
** Filename : boxModel.c
**
** Made by  : Baptiste LEGO
**
** Description  : getting data for box table
*/

#include <stdlib.h>
#include <stdio.h>
#include "../../headers/model/modelHelper/modelSelect.h"

void getBoxes(App *app){
    getSelectQuery(app, "SELECT * from box");
}
