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
#define MAX_CURRENT_VALUE 1000


void showQueryResult(char ****resultQuery, unsigned int *numberFields, unsigned int *numberRows, char **fieldsList) {

    if (fieldsList != NULL) {
        addFieldsToResult(resultQuery, &fieldsList, &numberRows);
    }

    showWellResult(*resultQuery, *numberFields, *numberRows, fieldsList);
}

void addFieldsToResult(char ****resultQuery, char ***fieldsList, unsigned int **numberRows) {
    char ***inter;
    int i;

    inter = malloc(sizeof(char**) * (++**numberRows));
    inter[0] = *fieldsList;

    for (i = 0; i < (**numberRows) - 1; i++) {

        inter[i + 1] = (*resultQuery)[i];
    }

    free(*resultQuery);

    (*resultQuery) = inter;
}

void showWellResult(char ***resultQuery, int numberFields, int numberRows, char **fieldsList) {
    int *maxLengthsFields = getMaxLengthOfEachFields(resultQuery, numberFields, numberRows);
    int i;
    int j;
    int z;

    addSpaceToGetSameLengthPerField(&resultQuery, numberFields, numberRows, maxLengthsFields);

    for (i = 0; i < numberRows; i++) {
        printf("|");
        for (j = 0; j < numberFields; j++) {
            printf(" %s |", resultQuery[i][j]);
        }
        printf("\n");
        if (i == 0 && fieldsList != NULL) {
            for (j = 0; j < numberFields; j++) {
                for (z = 0; z < maxLengthsFields[j]; z++) {
                    printf("_");
                }
                printf("___");
            }
            printf("\n");
        }
    }

    free(maxLengthsFields);
}

int *getMaxLengthOfEachFields(char ***resultQuery, int numberFields, int numberRows) {
    int i;
    int j;
    int *maxLengthsFields = malloc(sizeof(int) * numberFields);
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

void addSpaceToGetSameLengthPerField(char ****resultQuery, int numberFields, int numberRows, int *maxLengthsFields) {
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
