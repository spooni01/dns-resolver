/************************************************************
* Project:     	DNS resolver								*
* File:        	params.h  									*
* Date:        	23.09.2023									*
* Author: 		Adam Ližičiar <xlizic00@stud.fit.vutbr.cz>	*
*************************************************************/
#include <stdio.h>

/*
 * Params types 
 */
typedef struct Params {
    int r;
    int x;
    int _6;
    char *s;
    int p;
    char *address;
} params_t;
