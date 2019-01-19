/*
** Filename : list.h
**
** Made by  : Baptiste LEGO
**
** Description  : play mode main functions
*/

void listMenu(App *app, SelectQuery boxes, int page, int i);
void displayHomeBox(App *app, SDL_Rect *listButtons, SelectQuery lists);
int createListPage(App *app, SDL_Rect *buttons, int size);
