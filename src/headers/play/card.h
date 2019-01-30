/*
** Filename : card.h
**
** Made by  : Baptiste LEGO
**
** Description  : card functions
*/

void newCard(App *app, SelectQuery cards);
void cardResponse(App *app, char **card);

int randomCard(App *app, SelectQuery cards);
int numberOfValidCards(App *app, SelectQuery cards);
int isValidCard(char **card);

void displayCard(App *app, char **card, SDL_Rect *pageButton);
void displayResponse(App *app, char **card, SDL_Rect *pageButtons);
