/*
** Filename : cardModel.c
**
** Made by  : Baptiste LEGO
**
** Description  : data model for card table
*/

SelectQuery getAllCards(App *app);
SelectQuery getCardsFromList(App *app, int listId);
int resetCards(App *app, int listId);
int setNewCardValidation(App *app, char *cardId);
