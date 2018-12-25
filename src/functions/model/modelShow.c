/*
** Filename : mysqlShow.c
**
** Made by  : Masataka ISHII
**
** Description  : show the result of request
*/
#include <stdio.h>
#include <string.h>
#include "../../headers/model/modelShow.h"
#include "../../headers/model/modelSelect.h"

#define MAX_CURRENT_VALUE 1000

void showQueryResult(App *app, SelectQuery *selectQuery) {
    int numberFields = selectQuery->numberFields;
    int numberRows = selectQuery->numberRows;
    char ***resultQuery = NULL;
    int *maxLengthsFields;
    int i, j, k;

    copyListQuerySelect(app, &resultQuery, selectQuery);

    maxLengthsFields = getMaxLengthOfEachFields(app, resultQuery, numberFields, numberRows);
    addSpaceToGetSameLengthPerField(app, &resultQuery, numberFields, numberRows, maxLengthsFields);

    for (i = 0; i < numberRows; i++) {
        printf("|");
        for (j = 0; j < numberFields; j++) {
            printf(" %s |", resultQuery[i][j]);
        }
        printf("\n");

        for (j = 0; j < numberFields; j++) {
            for (k = 0; k < maxLengthsFields[j]; k++) {
                printf("_");
            }
            printf("___");
        }
        printf("\n");

    }

    free(maxLengthsFields);
    freeResultStringTable(resultQuery, numberFields, numberRows);
}

int *getMaxLengthOfEachFields(App *app, char ***resultQuery, int numberFields, int numberRows) {
    int i;
    int j;
    int *maxLengthsFields = malloc(sizeof(int) * numberFields);
    verifyPointer(app, maxLengthsFields, "Problem memory allocation in maxLengthsFields\n");

    if (maxLengthsFields == NULL) {
        printf("problem of calloc for maxLengthsFields");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < numberFields; i++) {
        maxLengthsFields[i] = 0;

        for (j = 0; j < numberRows; j++) {
            if (maxLengthsFields[i] < strlen(resultQuery[j][i])) {
                maxLengthsFields[i] = strlen(resultQuery[j][i]);
            }
        }
    }

    return maxLengthsFields;
}

void copyListQuerySelect(App *app, char ****resultQuery,SelectQuery *selectQuery){
    int i, j;
    int numberRows = selectQuery->numberRows;
    int numberFields = selectQuery->numberFields;
    char ***listToCopy = selectQuery->listColumnsRows;

    *resultQuery = malloc(sizeof(char**) * numberRows);
    verifyPointer(app, *resultQuery, "Problem memory allocation for resultQuery in copyListQuerySelect\n");
    for (i = 0; i < numberRows; i++){

        (*resultQuery)[i] = malloc(sizeof(char*) * numberFields);
        verifyPointer(app, (*resultQuery)[i], "Problem memory allocation for resultQuery[i] in copyListQuerySelect\n");
        for (j = 0; j < numberFields; j++) {

            (*resultQuery)[i][j] = malloc(sizeof(char) * (strlen(listToCopy[i][j]) + 1));
            strcpy((*resultQuery)[i][j], listToCopy[i][j]);
        }
    }
}

void addSpaceToGetSameLengthPerField(App *app, char ****resultQuery, int numberFields, int numberRows, int *maxLengthsFields) {
    int i;
    int j;
    int diffLength;
    char currentValue[MAX_CURRENT_VALUE];
    char *spaces;

    for (i = 0; i < numberFields; i++) {
        diffLength = 0;
        for (j = 0; j < numberRows; j++) {
            if (maxLengthsFields[i] > strlen((*resultQuery)[j][i])) {
                strcpy(currentValue, (*resultQuery)[j][i]);

                diffLength = maxLengthsFields[i] - strlen(currentValue);

                spaces = getSpaces(diffLength);

                (*resultQuery)[j][i] = realloc((*resultQuery)[j][i], sizeof(char) * (maxLengthsFields[i] + 1));
                strcat((*resultQuery)[j][i], spaces);
            }
        }
    }
}

char *getSpaces(int numberSpace) {
    int i;
    char *spaces = malloc(sizeof (char) * numberSpace);

    for (i = 0; i < numberSpace; i++) {
        spaces[i] = ' ';
    }
    spaces[numberSpace] = '\0';

    return spaces;
}
