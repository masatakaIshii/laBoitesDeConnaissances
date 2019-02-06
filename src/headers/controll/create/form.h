/*
** Filename : form.c
**
** Made by  : Masataka ISHII
**
** Description  : form functions for events
*/

#ifndef CREATE_FORM
#include "../../struct.h"
#include "../../model/formModel.h"
#include "../listRectAndChar.h"
#include "../textInput.h"
#include "../../view/create/createViewForm.h"
#include "verifyForm.h"

int createForm(App *app, char *tableName, char *idParent);
int eventForm(App *app, SDL_Event *event, InputManager *inputs, int *done, ListFields fields, QueryForm *qForm,  SDL_Rect submitButton, SDL_Rect successButton);

ListFields getListFieldsForForm(App *app, MySqlTable tableInfo);
int *adaptedIndexesToForm(App *app, MySqlTable tableInfo, int *numberField);
int *addIndexInArray(App *app, int *indexes, int index, int numberField);
InputManager *loadInputs(App *app, ListFields fields, int maxTextLength);

QueryForm loadQueryForm(App *app, char *tableName, ListFields fieldsForm, MySqlTable tableInfo, char *idParent);
void prepareInsertQuery(App *app, QueryForm *qForm, ListFields fieldsForm, MySqlTable tableInfo);
void putNowIfItIsDatetime(MySqlTable tableInfo, int index, Varchar *fields, Varchar *values);
void putIdParentInfo(MySqlTable tableInfo, int index, Varchar *fields, Varchar *values);
void putComma(MySqlTable tableInfo, int index, Varchar *fields, Varchar *values);
Varchar *getArrayStringForInsertQuery(App *app, Varchar listString, int *numberFields);
int getNumberOfFieldsInInsert(Varchar listString);

int submitButtonEvent(App *app, SDL_Event *event, InputManager *inputs, ListFields fields, QueryForm *qForm, SDL_Rect submitButton);
void quitForm(MySqlTable tableInfo, ListFields list, InputManager *inputs, QueryForm qForm);
void quitInputs(InputManager *inputs, int numberFields);
#endif // CREATE_FORM

