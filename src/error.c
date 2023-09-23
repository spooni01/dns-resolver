/************************************************************
* Project:     	DNS resolver								*
* File:        	errors.c  									*
* Date:        	23.09.2023									*
* Author: 		Adam Ližičiar <xlizic00@stud.fit.vutbr.cz>	*
*************************************************************/
#include <stdio.h>
#include "lib/error.h"

/*
 *  End program with stderr message
 */
void print_error(errors_t err) {
    char *txt;
    if(err == SUCCESS)
        exit(SUCCESS);

    // Parameters error
    else if(err == ERR_INCORRECT_PARAMETERS_FORMAT) 
        txt = "Incorrect usage, usage must be: ./dns [-r] [-x] [-6] -s server [-p port] address";
    else if(err == ERR_REQUIRED_ARGUMENTS_NOT_SET)
        txt = "Required arguments (server, address) are not set! See usage: ./dns [-r] [-x] [-6] -s server [-p port] address";

    // Other
    else
        txt = "Undefined!";

    fprintf(stderr, "\033[0;31mERROR: %s\033[0m\n", txt);
    exit(err);
}