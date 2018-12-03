/*
** Filename : mysqlShow.c
**
** Made by  : Masataka ISHII
**
** Description  : show the result of request
*/
#include <stdio.h>
#include "../../headers/model/modelShow.h"
/*
@TODO : Mettre en place un affichage bien structuré en prenant en compte la taille max de chaque colonne et nom de colonne
*/

void showQueryResult(char* ***resultResult,unsigned int* numberFields,unsigned int* numberRows, char **fieldsList) {
    int i;
    int j;


    if (fieldsList != NULL) {
        addFieldsToResult(resultResult, &fieldsList, &numberRows);
    }

    printf("numberFields : %u\n", *numberFields);
    printf("numberRows : %u\n", *numberRows);

    for (i = 0; i < *numberRows; i++) {
        for(j = 0; j < *numberFields; j++) {
            printf("%s | ", (*resultResult)[i][j]);
        }
        printf("\n");
    }

}

void addFieldsToResult(char* ***resultQuery, char* **fieldsList, unsigned int* *numberRows) {
    char ***inter;
    int i;

    inter = malloc(sizeof(char**) * (++**numberRows));
    inter = fieldsList;

    for (i = 0; i < (**numberRows); i++) {

        inter[i + 1] = (*resultQuery)[i];
    }

    free(*resultQuery);

    (*resultQuery) = inter;
}
