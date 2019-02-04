/*
** Filename : boxModel.h
**
** Made by  : Baptiste LEGO
**
** Description  : data model for box table
*/

#define ID                0
#define NAME              1
#define DESCRIPTION       2
#define B_CREATED_DATE    3
#define B_MODIFIED_DATE   4
#define B_COLOR           5

SelectQuery getBoxes(App *app);
