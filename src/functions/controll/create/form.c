/*
** Filename : form.c
**
** Made by  : Masataka ISHII
**
** Description  : form functions for events
*/
#include "../../../headers/controll/form.h"
/**
*@todo : block the addText to the maxLengthText
*@todo : verify the value of each input (make verification with pointer of function)
*@todo : show error if the value is not correct
*@todo : if after the second submit, the error is correct, then the char error is dissapear
*@todo :
*/

/**
*@brief : function of loop event of form
*
*@param (App *) app : the structure of application
*@param (SelectQuery *) table: adresse of all concerned elements that content in selectQuery
*@param (SDL_Rect *) listButton : list of all button correponded to select query
*@param (char *) tableName : the name of table to insert the information
*@param (int) idParent : the id of parent if the table contain foreign key
*/
int createForm(App *app, SelectQuery *table, SDL_Rect *listButton, char *tableName, int idParent){
    SDL_Event event;
    SDL_Rect submitButton;
    MySqlTable tableInfo = getTable(app, tableName);
    int done = 0;
    ListFields fields = getListFieldsForForm(app, tableInfo);
    InputManager *inputs = loadInputs(app, fields, 50);
    int checkForm = 0;

    SDL_StopTextInput();
    while (!done) {
        SDL_WaitEvent(&event);

        commonEvents(app, event, &done);

        checkForm = eventForm(app, &event, inputs, &done, fields.numberFields);

        displayAllForm(app, inputs, fields, tableName, &submitButton);
    }

    quitInputs(inputs, fields.numberFields);
    free(fields.list);
    free(tableInfo.listFieldsNames);
    free(tableInfo.listFieldsTypes);

    return checkForm;
}

/**
*@brief All events for form to make specific actions
*
*@param (App*) app : structure of application
*@param (SDL_Event*) event: structure of all event for SDL
*@param (InputManager*) inputs : structure for manage inputs texts
*@param (int*) done : bool for exit the loop of event
*@param (int) numberFields : number of inputs
*
*@return (int) checkForm : when form is submit and valid, exit the loop
*/
int eventForm(App *app, SDL_Event *event, InputManager *inputs, int *done, int numberFields){
    int checkForm = 0;
    int i;

    switch (event->type){
        case SDL_KEYDOWN:
            if (SDL_IsTextInputActive()){
                for (i = 0; i < numberFields; i++){
                    if (inputs[i].active == 1){
                        textInputKeyEvents(event, &inputs[i].textInput);
                    }
                }
            }
        break;
        case SDL_MOUSEBUTTONDOWN:
            if(event->button.button == SDL_BUTTON_LEFT){
                textInputButtonLeftEvents(app, event, inputs, numberFields);
            }
        break;
        case SDL_TEXTINPUT:
            for (i = 0; i < numberFields; i++){
                if (inputs[i].active == 1){
                    textInputEvents(app, event, &inputs[i].textInput);
                }
            }
        break;
    }

    return checkForm;
}


/**
*@brief Get list fields for the form
*
*@param (App *) app : structure of application
*@param (MySqlTable) tableInfo : informations of table via the database
*
*@return (ListFields) adaptedTable : structure contain list and number of fields for form
*/
ListFields getListFieldsForForm(App *app, MySqlTable tableInfo){
    ListFields adaptedTable;
    int *indexToTake = NULL;
    int i;

    adaptedTable.numberFields = 0;
    indexToTake = adaptedIndexesToForm(app, tableInfo, &adaptedTable.numberFields);

    adaptedTable.list = malloc(sizeof(Varchar) * adaptedTable.numberFields);
    verifyPointer(app, adaptedTable.list, "Problem malloc adaptedTable.list in getListFieldsForForm\n");

    for (i = 0; i < adaptedTable.numberFields; i++){
        strcpy(adaptedTable.list[i], tableInfo.listFieldsNames[indexToTake[i]]);
    }

    free(indexToTake);

    return adaptedTable;
}

/**
*@brief To get array and number of display fields name and type
*
*@param (App *) app : structure of application
*@param (int *) numberField : address of numberField of displayFields in form
*
*@return (int *) indexes : array of indexes correspond to fields to display in form
*/
int *adaptedIndexesToForm(App *app, MySqlTable tableInfo, int *numberField){
    int *indexes = NULL;
    int i;
    int canAddIndex = 0;

    for (i = 0; i < tableInfo.numberField; i++){
        if (strncmp(tableInfo.listFieldsNames[i], "id", 3) != 0 && strncmp(tableInfo.listFieldsNames[i], "id_", 3) != 0 && tableInfo.listFieldsTypes[i] != MYSQL_TYPE_DATETIME){
            canAddIndex = 1;
        }

        if (canAddIndex == 1){
            (*numberField)++;
            indexes = addIndexInArray(app, indexes, i, *numberField);
            canAddIndex = 0;
        }
    }

    return indexes;
}

/**
*@brief add first index in indexes of add in last case
*
*@param (App*) app : structure of application
*@param (int*) indexes : array dyn of index
*@param (int) index : index to add in indexes
*@param (int) numberField : number of fields with new index
*
*@return (int*) inter : new indexes with adding index
*/
int *addIndexInArray(App *app, int *indexes, int index, int numberField){
    int* inter;
    int i;

    if(indexes == NULL && numberField == 1){
        inter = malloc(sizeof(int));
        inter[0] = index;
    } else if (indexes != NULL){
        inter = malloc(sizeof(int) * numberField);
        for (i = 0; i < (numberField - 1) ; i++){
            inter[i] = indexes[i];
        }
        inter[numberField - 1] = index;
        free(indexes);
    } else {
        printf("Problem values of numberFields in addIndexInArray\n");
        quitApp(app);
        return EXIT_FAILURE;
    }

    return inter;
}

/**
*function to load the structure InputManager and define the max of length of input\n
*
*@param (App*) app : structure of application
*@param (ListFields) fields : structure of fields
*@param (int) maxTextLength : max length of each input
*
*@return (InputManager*) : array of structure InputManager
*/
InputManager *loadInputs(App *app, ListFields fields, int maxTextLength){
    int i;
    InputManager *inputs = malloc(sizeof(InputManager) * fields.numberFields);
    verifyPointer(app, inputs, "Problem malloc inputs in createForm");

    for (i = 0; i < fields.numberFields; i++){
        inputs[i].active = 0;
        strcpy(inputs[i].error, "");
        strcpy(inputs[i].label, fields.list[i]);
        inputs[i].textInput.listChar = NULL;
        inputs[i].textInput.maxLength = maxTextLength;
        inputs[i].textInput.size = 0;
        inputs[i].textInput.nbChar = 0;
        inputs[i].textInput.start = 0;
    }

    return inputs;
}

void quitInputs(InputManager *inputs, int numberFields){
    int i;

    for (i = 0;i < numberFields; i++){
        deleteAllListInputText(inputs[i].textInput.listChar);
    }
}
