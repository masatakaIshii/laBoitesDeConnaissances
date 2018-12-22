/*
** Filename : modelverificator.c
**
** Made by  : Masataka ISHII
**
** Description  : function to check the param and the query for fill the structure TableMysql
*/
#include <stdio.h>
#include <string.h>
#include "../../headers/model/modelVerificator.h"
#define MAX 1000

//TODO : verifier si la requête est correct (si c'est un select ou si c'est un IUD)

/**
*@brief Compare if numberMark in query is equal to numberParams
*
*@param query : the query that normally content question marks
*@param numberParams : number parameter for prepared query
*@return 1 if is equal, else 0 if it is not equal
*/
short numberOfQMarkAndParamsIsEqual(const char *query, int numberParams) {
    int numberQMark = 0;
    char temp[MAX];
    short result;
    char *target;

    strcpy(temp, query);

    while(strchr(temp, '?') != NULL) {
        target = strchr(temp, '?');
        if (target) {
            temp[target - temp] = '_';
            numberQMark++;
        }
    }

    result = (numberQMark == numberParams) ? 1 : 0;

    return result;
}
