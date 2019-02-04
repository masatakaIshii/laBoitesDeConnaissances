/*
** Filename : boxModel.c
**
** Made by  : Baptiste LEGO
**
** Description  : data model for box table
*/

#include <stdlib.h>
#include <stdio.h>
#include "../../headers/model/modelHelper/modelSelect.h"

SelectQuery getBoxes(App *app){
    return getSelectQuery(app, "SELECT * from box");
}
