/*
** Filename : boxModel.h
**
** Made by  : Baptiste LEGO
**
** Description  : data model for box table
*/

#define ID                0
#define NAME              1
#define B_CREATED_DATE    2
#define B_MODIFIED_DATE   3
#define B_COLOR           4

SelectQuery getBoxes(App *app);
