/*
** Filename : createViewFrom.h
**
** Made by  : Masataka ISHII
**
** Description  : view form functions
*/

#ifndef CREATE_VIEW_FORM
#include "../../struct.h"
#include "../../common.h"
#include "../../controll/textInput.h"

void displayAllForm(App *app, InputManager *input, ListFields fields, char *tableName, SDL_Rect *submitButton);
void createInputs(App *app, InputManager *input, ListFields fields);
SDL_Rect getPositionOfText(SDL_Rect inputRect, int maxLength);

int getAppropriateWidth(SDL_Rect commonRect, int length, int maxLength);

void renderAllForm(App *app, SDL_Rect titleRect, char *title, SDL_Rect *submitButton, InputManager *input, ListFields fields);
void displayAllTextInputs(App *app, InputManager *inputs, int numberFields);
void displaySuccessForm(App *app, SDL_Rect successButton);

#endif // CREATE_VIEW_FORM
