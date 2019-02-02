/*
** Filename : box.h
**
** Made by  : Baptiste LEGO
**
** Description  : box menu headers
*/

void playMode(App *app);
void displayHomePlay(App *app, SelectQuery boxes, int page, SDL_Rect *pageButtons, SDL_Rect *boxButtons, int *nbOfBoxInPage);
int createBoxPage(App *app, SelectQuery boxes, SDL_Rect *buttons, int size, int page);
void renderButtonLabel(App *app, char **data, SDL_Rect buttonPos);
