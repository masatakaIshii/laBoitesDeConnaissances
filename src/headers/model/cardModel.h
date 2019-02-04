/*
** Filename : cardModel.c
**
** Made by  : Baptiste LEGO
**
** Description  : data model for card table
*/

#define ID                0
#define NAME              1
#define C_CREATED_DATE    2
#define QUESTION          3
#define ANSWER            4
#define ID_LIST           5
#define COUNT             6
#define VALIDATED_DATE    7
#define C_MODIFIED_DATE   8

SelectQuery getAllCards(App *app);
SelectQuery getCardsFromList(App *app, int listId);
int resetCards(App *app, int listId);
int setNewCardValidation(App *app, char *cardId);
