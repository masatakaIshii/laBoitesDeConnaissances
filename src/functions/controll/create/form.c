/*
** Filename : form.c
**
** Made by  : Masataka ISHII
**
** Description  : form functions for events
*/
#include "../../../headers/controll/create/form.h"

/**
*@brief : function of loop event of form
*
*@param (App *) app : the structure of application
*@param (SelectQuery *) table: adresse of all concerned elements that content in selectQuery
*@param (SDL_Rect *) listButton : list of all button correponded to select query
*@param (char *) tableName : the name of table to insert the information
*@param (int) idParent : the id of parent if the table contain foreign key
*@return (int) return : 1 => the form is valid, 0 => nothing
*/
int createForm(App *app, SelectQuery *table, char *tableName, int idParent){
    SDL_Event event;
    SDL_Rect submitButton;
    SDL_Rect successButton;
    int done = 0;
    MySqlTable tableInfo = getTable(app, tableName);
    ListFields fields = getListFieldsForForm(app, tableInfo);
    InputManager *inputs = loadInputs(app, fields, 50);
    QueryForm qForm = loadQueryForm(app, tableName, fields, tableInfo, idParent);
    int checkForm = 0;

    SDL_StopTextInput();
    while (!done) {
        SDL_WaitEvent(&event);

        commonEvents(app, event, &done);

        checkForm = eventForm(app, &event, inputs, &done, fields, &qForm, submitButton, successButton);

        if (checkForm == 0){
            displayAllForm(app, inputs, fields, tableName, &submitButton);
        } else if (checkForm > 0){
            done = 1;
        }

        SDL_RenderPresent(app->renderer);
    }

    quitForm(tableInfo, fields, inputs, qForm);

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
int eventForm(App *app, SDL_Event *event, InputManager *inputs, int *done, ListFields fields, QueryForm *qForm,  SDL_Rect submitButton, SDL_Rect successButton){
    int checkForm = 0;
    int i;

    switch (event->type){
        case SDL_KEYDOWN:
            if (SDL_IsTextInputActive()){
                for (i = 0; i < fields.numberFields; i++){
                    if (inputs[i].active == 1){
                        textInputKeyEvents(event, &inputs[i].textInput);
                    }
                }
            }
        break;
        case SDL_MOUSEBUTTONDOWN:
            if(event->button.button == SDL_BUTTON_LEFT){

                textInputButtonLeftEvents(app, event, inputs, fields.numberFields);

                checkForm = submitButtonEvent(app, event, inputs, fields, qForm, submitButton);
                //*done = 1;
            }
        break;
        case SDL_TEXTINPUT:
            for (i = 0; i < fields.numberFields; i++){
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
        if (tableInfo.listFieldsTypes[i] != MYSQL_TYPE_LONG && tableInfo.listFieldsTypes[i] != MYSQL_TYPE_DATETIME){
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
        strcpy(inputs[i].label, fields.list[i]);
        strcpy(inputs[i].error, "");
        inputs[i].textInput.listChar = NULL;
        inputs[i].textInput.maxLength = maxTextLength;
        inputs[i].textInput.size = 0;
        inputs[i].textInput.nbChar = 0;
        inputs[i].textInput.start = 0;
    }

    return inputs;
}

QueryForm loadQueryForm(App *app, char *tableName, ListFields fieldsForm, MySqlTable tableInfo, int idParent){
    QueryForm newForm;
    newForm.idParent = idParent;
    newForm.fields = NULL;
    newForm.values = NULL;
    newForm.numberFields = 0;

    strcpy(newForm.tableName, tableName);

    prepareInsertQuery(app, &newForm, fieldsForm, tableInfo);

    return newForm;
}

void prepareInsertQuery(App *app, QueryForm *qForm, ListFields fieldsForm, MySqlTable tableInfo){
    Varchar temp = "";
    Varchar fields = "";
    Varchar values = "";
    void (*conditions[3])(MySqlTable, int, Varchar*, Varchar*) = {putNowIfItIsDatetime, putIdParentInfo, putComma};
    int i;
    int j;

    for (i = 0; i < tableInfo.numberField; i++){
        for (j = 0;j < fieldsForm.numberFields; j++){
            if (strcmp(tableInfo.listFieldsNames[i], fieldsForm.list[j]) == 0){
                strcat(fields, tableInfo.listFieldsNames[i]);
                strcat(values, "?");
                break;
            }
        }
        for (j = 0; j < 3; j++){
            conditions[j](tableInfo, i, &fields, &values);
        }
    }

    sprintf(temp, "INSERT INTO %s (%s) VALUES (%s)", qForm->tableName, fields, values);
    strcpy(qForm->query, temp);
    qForm->fields = getArrayStringForInsertQuery(app, fields, &qForm->numberFields);
}

void putNowIfItIsDatetime(MySqlTable tableInfo, int index, Varchar *fields, Varchar *values){
    if (tableInfo.listFieldsTypes[index] == MYSQL_TYPE_DATETIME){
        strcat(*fields, tableInfo.listFieldsNames[index]);
        strcat(*values, "NOW()");
    }
}

void putIdParentInfo(MySqlTable tableInfo, int index, Varchar *fields, Varchar *values){
    if (strncmp(tableInfo.listFieldsNames[index], "id_", 3) == 0){
        strcat(*fields, tableInfo.listFieldsNames[index]);
        strcat(*values, "?");
    }
}

void putComma(MySqlTable tableInfo, int index, Varchar *fields, Varchar *values){
    if (index < (tableInfo.numberField - 1) && !(strncmp(tableInfo.listFieldsNames[index], "id", 3) == 0 || strcmp(tableInfo.listFieldsNames[index], "count") == 0 || index == 0)){
        strcat(*fields, ", ");
        strcat(*values, ", ");
    }
}

Varchar *getArrayStringForInsertQuery(App *app, Varchar listString, int *numberFields){
    Varchar *arrayFields = NULL;
    char *delimiter = ", ";
    char *token;
    int i = 0;
    Varchar temp;

    strcpy(temp, listString);
    *numberFields = getNumberOfFieldsInInsert(temp);

    arrayFields = malloc(sizeof(Varchar) * (*numberFields));
    token = strtok(temp, delimiter);
    while(token != NULL){
        if (strstr(token, "_date") == NULL && strcmp(token, "count") != 0){
            strcpy(arrayFields[i], token);
            i++;
        }
        token = strtok(NULL, delimiter);
    }

    return arrayFields;
}

int getNumberOfFieldsInInsert(Varchar listString){
    Varchar temp;
    int numberFields = 0;
    char *token;
    char *delimiter = ", ";

    strcpy(temp, listString);
    token = strtok(temp, delimiter);
    while(token != NULL){
        if (strstr(token, "_date") == NULL && strcmp(token, "count") != 0){
            numberFields++;
        }
        token = strtok(NULL, delimiter);
    }
    printf("numberFields : %d\n", numberFields);

    return numberFields;
}

int submitButtonEvent(App *app, SDL_Event *event, InputManager *inputs, ListFields fields, QueryForm *qForm, SDL_Rect submitButton){

    int check = 0;

    if (inRect(submitButton, event->button.x, event->button.y)){
        check = verifyInputsValues(app, inputs, fields, qForm);
    }

    return check;
}

/* -- quit form variables with malloc --*/
void quitForm(MySqlTable tableInfo, ListFields fields, InputManager *inputs, QueryForm qForm){
    free(qForm.fields);

    free(qForm.values);
    quitInputs(inputs, fields.numberFields);
    free(fields.list);
    free(tableInfo.listFieldsNames);
    free(tableInfo.listFieldsTypes);
}

void quitInputs(InputManager *inputs, int numberFields){
    int i;

    for (i = 0;i < numberFields; i++){
        deleteAllListInputText(inputs[i].textInput.listChar);
    }
}
