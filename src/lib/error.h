/************************************************************
* Project:     	DNS resolver								*
* File:        	errors.h  									*
* Date:        	23.09.2023									*
* Author: 		Adam Ližičiar <xlizic00@stud.fit.vutbr.cz>	*
*************************************************************/
#include <stdio.h>

/*
 * Error types 
 */
typedef enum
{
    SUCCESS                             = 0,  // No error

    // Parameters error
    ERR_INCORRECT_PARAMETERS_FORMAT     = 10, 
    ERR_REQUIRED_ARGUMENTS_NOT_SET      = 11,

    // Other
    ERR_UNDEFINED                       = 100 // Undefined error
} errors_t;