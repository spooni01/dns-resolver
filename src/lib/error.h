/************************************************************
* Project:     	DNS resolver								*
* File:        	errors.h  									*
* Date:        	23.09.2023									*
* Author: 		Adam Ližičiar <xlizic00@stud.fit.vutbr.cz>	*
*************************************************************/

#include <stdio.h>

typedef enum
{
    SUCCESS                             = 0,  // No error

    // Other
    ERR_UNDEFINED                       = 100 // Undefined error
} errors_t;