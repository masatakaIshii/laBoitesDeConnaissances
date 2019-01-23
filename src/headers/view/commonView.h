/*
** Filename : commonView.c
**
** Made by  : Masataka ISHII
**
** Description  : common view boxes functions
*/
#ifndef COMMON_VIEW
#include "../struct.h"
#include "../common.h"
DisplayManager displayManagerConstructor(int elementHeight, int elementWidth,
                                         int nbColomns, int nbRows,
                                         int startX, int startY,
                                         int stepX, int stepY);

int createCustumElementsPage(App *app, SDL_Rect *buttons, int sizeElements, int page, DisplayManager display);

#endif // COMMON_VIEW


