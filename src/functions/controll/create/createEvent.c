/*
** Filename : createEvent.c
**
** Made by  : Masataka ISHII
**
** Description  : create menu functions for events
*/
#include "../../../headers/controll/create/createEvent.h"

void createEventElements(App *app, SelectQuery *elements, SDL_Event *event, CreateInfo *cInfo, CreateButtons *cButton, CreatePage *cPages) {
    int i;

    int currentId =  cPages->page * elements->numberFields;
    int check = 0;
     //Change the page
    if (inRect(cPages->pageButtons[0], event->button.x, event->button.y)) {
        (cPages->page)--;
        printf("ca page--\n");
    } else if(inRect(cPages->pageButtons[1], event->button.x, event->button.y)) {
        (cPages->page)++;
        printf("ca page++\n");
    }
//
//    if (inRect(manageButtons[0], event.button.x, event.button.y)) {
//        check = createForm(app, boxes, boxButtons, "box", 0);
//        if(check == 1){
//
//        }
//    }
//    if (inRect(manageButtons[1], event.button.x, event.button.y)) {
//
//    }
//
//    for (i = currentId ; i < (currentId + boxes->numberFields); i++) {
//        if (inRect(boxButtons[i], event.button.x, event.button.y)){
//            //createModeList(app, boxes->listColumnsRows[i]);
//        }
//    }
}

//void eventPages(SDL_Event event)
