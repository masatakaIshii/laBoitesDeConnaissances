/*
** Filename : textInput.c
**
** Made by  : Masataka ISHII
**
** Description  : text input function functions
*/
#ifndef TEXTS_INPUT
#include "../struct.h"
#include "../common.h"
#include "listRectAndChar.h"

void initTextsInput(TextsInput *input);

void textInputKeyEvents(SDL_Event *event, TextsInput *input);
void textInputButtonLeftEvents(App *app, SDL_Event *event, InputManager *inputs, int numberFields);
void textInputEvents(App *app, SDL_Event *event, TextsInput *input);
int adaptWForTexts(int wOneChar, int nbChar);
void displayInput(App *app, TextsInput input, Uint8 *rectColor, SDL_Rect textPos);

#endif // TEXTS_INPUT

