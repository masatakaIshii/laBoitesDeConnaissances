/*
** Filename : list.c
**
** Made by  : Baptiste LEGO
**
** Description  : play mode main functions
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "../../headers/common.h"
#include "../../headers/play/box.h"
#include "../../headers/play/list.h"

void listMenu(App *app, int page, int i){
    printf("Liste numero %d\n", i+page*63);
}
