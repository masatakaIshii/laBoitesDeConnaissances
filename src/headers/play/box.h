/*
** Filename : box.h
**
** Made by  : Baptiste LEGO
**
** Description  : play mode main functions
*/

void playMode(App *app);
void displayHomePlay(App *app, SelectQuery boxes, int page, SDL_Rect *pageButtons, SDL_Rect *boxButtons, int *nbOfBoxInPage, int nbTotalOfBox);
int createBoxPage(App *app, SelectQuery boxes, SDL_Rect *buttons, int size, int page);


