/*
** Filename : box.h
**
** Made by  : Baptiste LEGO
**
** Description  : play mode main functions
*/

void playMode(App *app);
void displayHomePlay(App *app, int page, SDL_Rect *pageButtons, SDL_Rect *boxButtons, int *nbOfBox);
int createBoxPage(App *app, SDL_Rect *buttons, char *box, int size, int page);
