#ifndef TEST_FUNCTIONS
#include "../struct.h"
#include "listRectAndChar.h"

typedef enum KeyAction{
    STAND_BY,
    C_RIGHT,
    C_LEFT,
    ADD_CHAR,
    B_DELETE,
    R_DELETE,
    SB_DELETE
} KeyAction;


typedef struct TextsInput{
    ListInputText *listChar;
    int size;
    int nbChar;
    int cursor;
    int start;
    int end;
    KeyAction action;
} TextsInput;


int testEventLoop(App *app);
void loadTextsInput(TextsInput *input);

void textInputKeyEvents(SDL_Event event, TextsInput *input);
void textInputEvents(App *app, SDL_Event event, TextsInput *input);
void addCharInInputString(TextsInput *input, char *oneChar);
void removeCharBeforeCursor(TextsInput *input);

void displayInput(App *app, TextsInput *input);
int adaptWForTexts(int wOneChar, int nbChar);
#endif


