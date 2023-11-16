/************************************************************
* Project:     	DNS resolver								*
* File:        	main.hpp	    							*
* Date:        	15.11.2023									*
* Author: 		Adam Ližičiar <xlizic00@stud.fit.vutbr.cz>	*
*************************************************************/

#ifndef MAIN_H
#define MAIN_H

    #include <iostream>
    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <netdb.h>
    #include <stdint.h>
    #include <string>
    #include <vector>
    #include <algorithm>
    #include <iomanip>
    #include <stdlib.h>
    #include <regex>
    #include <unistd.h>
    #include <string.h>

    #include "ansi_colors.hpp"
    #include "dns_structures.hpp"
    #include "dns_constants.hpp"

    #include "../classes/Error/Error.cpp"
    #include "../classes/Arguments/Arguments.cpp"
    #include "../classes/DNS/DnsRequestSender.cpp"
    #include "../classes/DNS/DnsResponseReceiver.cpp"

#endif
