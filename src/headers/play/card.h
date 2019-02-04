/*
** Filename : card.h
**
** Made by  : Baptiste LEGO
**
** Description  : card headers
*/

void newCard(App *app, SelectQuery cards, char *backgroundColor);
void cardResponse(App *app, char **card, char *backgroundColor);

int randomCard(App *app, SelectQuery cards);
int numberOfValidCards(App *app, SelectQuery cards);
int isValidCard(char **card);

void displayCard(App *app, char **card, SDL_Rect *pageButton, char *backgroundColor);
void displayResponse(App *app, char **card, SDL_Rect *pageButtons, char *backgroundColor);
