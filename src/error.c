/************************************************************
* Project:     	DNS resolver								*
* File:        	errors.c  									*
* Date:        	23.09.2023									*
* Author: 		Adam Ližičiar <xlizic00@stud.fit.vutbr.cz>	*
*************************************************************/

#include <stdio.h>
#include "lib/error.h"

void print_error(errors_t err) {
    char *txt;
    if(err == SUCCESS)
        exit(0);
    else
        txt = "Undefined!";

    fprintf(stderr, "\033[0;31mERROR: %s\033[0m", txt);
    exit(err);
}