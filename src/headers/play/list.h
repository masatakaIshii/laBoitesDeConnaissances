/*
** Filename : list.h
**
** Made by  : Baptiste LEGO
**
** Description  : list menu headers
*/

void listMenu(App *app, SelectQuery boxes, int page, int i);
int displayHomeBox(App *app, SelectQuery lists, SDL_Rect *listButtons, char *boxTitle, int *id);
int createListPage(App *app, SelectQuery lists, SDL_Rect *buttons,int *id, int size);
