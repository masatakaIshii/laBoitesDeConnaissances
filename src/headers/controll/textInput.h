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

void initTextsInput(TextsInput *input);

void textInputKeyEvents(SDL_Event event, TextsInput *input);
void textInputEvents(App *app, SDL_Event *event, TextsInput *input);
int adaptWForTexts(int wOneChar, int nbChar);

#endif // TEXTS_INPUT

