/*
** Filename : form.c
**
** Made by  : Masataka ISHII
**
** Description  : form functions for events
*/
#include "../../../headers/controll/form.h"

void createForm(App *app, SelectQuery *table, SDL_Rect *listButton, char *tableName){
    SDL_Event event;
    MySqlTable tableInfo;
    int done = 0;

    tableInfo =  getTable(app, tableName);

    while (!done) {
        SDL_WaitEvent(&event);
        commonEvents(app, event, &done);
        switch (event.type){
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button) {

                }
        }
    }
}
