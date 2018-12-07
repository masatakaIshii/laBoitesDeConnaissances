#include "struct.h"

int mainEventLoop(App *app);
void displayMenu(App *app);
void resizeScreen(App *app, int height);
void createRect(App *app, int width, int height, int x, int y, int* color);
void verifyPointer(App *app, void *pointer, char* message);
void loadConfig(Config *config, int height);
void loadColors(Colors *colors);
void loadApp(App *app);
void quitApp(App *app);
