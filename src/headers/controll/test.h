#ifndef TEST_FUNCTIONS
#include "../struct.h"
#include "listRectAndChar.h"

int testEventLoop(App *app);
//void loadTextsInput(TextsInput *input);

void textInputKeyEvents(SDL_Event event, TextsInput *input);
void textInputEvents(App *app, SDL_Event event, TextsInput *input);
void addCharInInputString(TextsInput *input, char *oneChar);
void removeCharBeforeCursor(TextsInput *input);

//void displayInput(App *app, TextsInput *input);
int adaptWForTexts(int wOneChar, int nbChar);
#endif


