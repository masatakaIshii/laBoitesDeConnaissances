/*
** Filename : createEvent.c
**
** Made by  : Masataka ISHII
**
** Description  : create menu functions for events
*/
#include "../../../headers/controll/create/createEvent.h"
#include "../../../headers/controll/create/create.h"

int createEventElements(App *app, SelectQuery *elements, SDL_Event *event, CreateInfo *cInfo, CreateButtons *cButton, CreatePage *cPages, char *tableName) {
    int i;

    int currentId;
    int check = 0;
     //Change the page

    createPageEvent(app, event, cButton, cPages);
    if (inRect(cButton->manageButtons[0], event->button.x, event->button.y)) {
        check = createForm(app, elements, tableName, cInfo->idParent);
    }
//    if (inRect(manageButtons[1], event.button.x, event.button.y)) {
//
//    }
//
    for (i = 0; i < cPages->nbElementsPage; i++) {
        if (inRect(cPages->elementButtons[i], event->button.x, event->button.y)){
            currentId = cPages->page * cPages->nbElementMaxPerPage + i;
            printf("page : %d\n", cPages->page);
            printf("i : %d\n", i);
            printf("nbElementsPage : %d\n", cPages->nbElementMaxPerPage);
            printf("currentId : %d\n", currentId);
            createMode(app, cInfo->childTable, elements->listColumnsRows[currentId]);
        }
    }

    return check;
}

void createPageEvent(App *app, SDL_Event *event, CreateButtons *cButton, CreatePage *cPages){
    if (inRect(cPages->pageButtons[0], event->button.x, event->button.y)) {
        (cPages->page)--;
        cButton->activeDel = 0;
    } else if(inRect(cPages->pageButtons[1], event->button.x, event->button.y)) {
        (cPages->page)++;
        cButton->activeDel = 0;
    }
}

//void eventPages(SDL_Event event)
