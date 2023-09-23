/************************************************************
* Project:     	DNS resolver								*
* File:        	params.c  									*
* Date:        	23.09.2023									*
* Author: 		Adam Ližičiar <xlizic00@stud.fit.vutbr.cz>	*
*************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lib/params.h"

/*
 * Save params from argv to struct params_t
 */
params_t getParams(int argc, char *argv[]) {
    params_t params = {0, 0, 0, NULL, 53, NULL};
    int opt;

    while ((opt = getopt(argc, argv, "rx6s:p:")) != -1) {
        switch (opt) {
            case 'r':
                params.r = 1;
                break;
            case 'x':
                params.x = 1;
                break;
            case '6':
                params._6 = 1;
                break;
            case 's':
                params.s = optarg;
                break;
            case 'p':
                params.p = atoi(optarg);
                break;
            default:
                print_error(ERR_INCORRECT_PARAMETERS_FORMAT);
        }
    }

    // Set address (todo, address can be also in the middle)
    for (int i = optind; i < argc; i++) {
        if (params.address == NULL) {
            params.address = argv[i];
            break;
        }
    }

    // Check required arguments
    if (params.s == NULL || params.address == NULL)
        print_error(ERR_REQUIRED_ARGUMENTS_NOT_SET);

    return params;
}