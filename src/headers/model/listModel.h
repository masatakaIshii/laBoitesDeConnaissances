/*
** Filename : listModel.h
**
** Made by  : Baptiste LEGO
**
** Description  : data model for list table
*/

#define ID                0
#define NAME              1
#define L_CREATED_DATE    2
#define L_MODIFIED_DATE   3
#define L_COLOR           4
#define ID_BOX            5

SelectQuery getAllLists(App *app);
SelectQuery getListsFromBox(App *app, char *boxId);
