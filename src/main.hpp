/************************************************************
* Project:     	DNS resolver								*
* File:        	main.hpp	    							*
* Date:        	11.10.2023									*
* Author: 		Adam Ližičiar <xlizic00@stud.fit.vutbr.cz>	*
*************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

// ANSI color codes for terminal output
#define ANSI_RESET "\033[0m"
#define ANSI_BOLD "\033[1m"
#define ANSI_BLUE "\033[34m"
#define ANSI_RED "\033[31m"

#include "Error/Error.cpp"
#include "Arguments/Arguments.cpp"
#include "DNS/DnsRequestSender.cpp"
#include "DNS/DnsResponseReceiver.cpp"
