#ifndef TEST_FUNCTIONS
#include "../struct.h"

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
    char texts[MAX_TEXT];
    int length;
    int cursor;
    int start;
    int end;
    KeyAction action;
} TextsInput;

int testEventLoop(App *app);
void textInputKeyEvents(SDL_Event event, TextsInput *input, short *startInput);
void textInputEvents(App *app, SDL_Event event, TextsInput *input);
void addCharInInputString(TextsInput *input, char *oneChar);
void removeCharBeforeCursor(TextsInput *input);

void displayInput(App *app, SDL_Rect buttonInput, TextsInput *input);
int adaptWForTexts(int wOneChar, int nbChar);
#endif


