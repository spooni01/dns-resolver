/************************************************************
* Project:     	DNS resolver								*
* File:        	src/libraries/dns_constants.hpp	           	*
* Date:        	15.11.2023									*
* Author: 		Adam Ližičiar <xlizic00@stud.fit.vutbr.cz>	*
*************************************************************/

#ifndef DNS_CONSTANTS
#define DNS_CONSTANTS

    #define DNS_SIZE_MAXIMUM 512

    // Type
    #define A 1
    #define NS 2
    #define MD 3
    #define MF 4
    #define CNAME 5
    #define SOA 6
    #define MB 7
    #define MG 8
    #define MR 9
    #define NULL_R 10
    #define WKS 11
    #define PTR 12
    #define HINFO 13
    #define MINFO 14
    #define MX 15
    #define TXT 16
    #define AAAA 28
    #define SRV 33

    // Class
    #define IN 1
    #define CS 2
    #define CH 3
    #define HS 4

#endif