/*
** Filename : list.h
**
** Made by  : Baptiste LEGO
**
** Description  : play mode main functions
*/

void listMenu(App *app, SelectQuery boxes, int page, int i);
void displayHomeBox(App *app, SelectQuery lists, SDL_Rect *listButtons, char *boxTitle);
int createListPage(App *app, SelectQuery lists, SDL_Rect *buttons, int size);
