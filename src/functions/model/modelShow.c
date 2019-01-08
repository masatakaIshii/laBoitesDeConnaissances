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

void showQueryResult(App *app) {

    SelectQuery *selectQuery    = &app->model.query.selectQuery;
    int numberFields            = selectQuery->numberFields;
    int numberRows              = selectQuery->numberRows;
    int *maxLengthsFields;

    maxLengthsFields = getMaxLengthOfEachFields(app, selectQuery->listColumnsRows, numberFields, numberRows);

    showAppropriateQueryResult(selectQuery, maxLengthsFields, numberFields, numberRows);

    free(maxLengthsFields);
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

void showAppropriateQueryResult(SelectQuery *selectQuery, int *maxLengthsFields, int numberFields, int numberRows) {

    int diffLength;
    int i, j, k;

    for (i = 0; i < numberRows; i++) {
        printf("|");
        for (j = 0; j < numberFields; j++) {
            printf(" %s ", selectQuery->listColumnsRows[i][j]);
            diffLength = maxLengthsFields[j] - strlen(selectQuery->listColumnsRows[i][j]);
            for (k = 0; k < diffLength; k++) {
                printf(" ");
            }
            printf("|");
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
}
