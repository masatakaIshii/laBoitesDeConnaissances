/*
** Filename : stats.h
**
** Made by  : Baptiste LEGO
**
** Description  : stats functions
*/

void stats(App *app);

int countRightAnswers(App *app, SelectQuery cards);

void displayStats(App *app, SelectQuery boxes, SelectQuery lists, SelectQuery cards);
void writeStats(App *app, SelectQuery boxes, SelectQuery lists, SelectQuery cards);
void printNumberStat(App *app, SDL_Rect textPos, char *description, int number);
