/************************************************************
* Project:     	DNS resolver								*
* File:        	Error.hpp									*
* Date:        	15.11.2023									*
* Author: 		Adam Ližičiar <xlizic00@stud.fit.vutbr.cz>	*
*************************************************************/	

enum ErrCode {
    ERR_NONE = 0,

    // Build errors
    ERR_BUILD                           = 1,

    // Arguments errors
    ERR_ARG_INVALID_ARGUMENT            = 10,
    ERR_ARG_UNUSUAL_PARAMETER           = 11,
    ERR_ARG_MISSING_SERVER              = 12,
    ERR_ARG_CAN_NOT_BE_X_AND_IPV6       = 13,
    ERR_ARG_IS_NOT_IPV4_ADDRESS         = 14,
    ERR_ARG_IS_NOT_IPV6_ADDRESS         = 15,
    ERR_ARG_IS_NOT_WEBSITE              = 16,

    // DNS request sender errors
    ERR_DNS_S_UNABLE_LOAD_SERVER        = 30,
    ERR_DNS_S_SOCKET_WAS_NOT_CREATED    = 31,
    ERR_DNS_S_DNS_CONNECTION_FAILED     = 32,
    ERR_DNS_S_UNABLE_LOAD_DNS_SERVER    = 33,
    ERR_DNS_S_IP_ADDRESS_NOT_FOUND      = 34,
    ERR_DNS_S_RESPONSE_FAILED           = 35,

    // DNS response receiver errors
    ERR_DNS_T_UNDEFINED                 = 70,

    // Tests errors
    ERR_TESTS_UNDEFINED                 = 80,

    // Documentation errors
    ERR_DOC_UNDEFINED                   = 90,

    // Other
    ERR_UNDEFINED                       = 100,
};