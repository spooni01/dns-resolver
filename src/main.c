/************************************************************
* Project:     	DNS resolver								*
* File:        	main.c  									*
* Date:        	23.09.2023									*
* Author: 		Adam Ližičiar <xlizic00@stud.fit.vutbr.cz>	*
*************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "error.c"
#include "params.c"

int main(/*int argc, char *argv[]*/) {
    //params_t params = getParams(argc, argv);
    
    /*****/
    /*printf("r: %d\n", params.r);
    printf("x: %d\n", params.x);
    printf("6: %d\n", params._6);
    printf("s: %s\n", params.s);
    printf("p: %d\n", params.p);
    printf("address: %s\n", params.address);*/
    /*****/
    printf("hello");

    return SUCCESS;
}