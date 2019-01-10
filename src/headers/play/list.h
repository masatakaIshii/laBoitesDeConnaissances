/*
** Filename : list.h
**
** Made by  : Baptiste LEGO
**
** Description  : play mode main functions
*/

void listMenu(App *app, int page, int i);
void displayHomeBox(App *app, SDL_Rect *listButtons);
int createListPage(App *app, SDL_Rect *buttons, char *list, int size);
