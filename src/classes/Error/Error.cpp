/************************************************************
* Project:     	DNS resolver								*
* File:        	Error.cpp									*
* Date:        	20.10.2023									*
* Author: 		Adam Ližičiar <xlizic00@stud.fit.vutbr.cz>	*
*************************************************************/	

#include "Error.hpp"

// Class will print error message and exit program 
class Error {
    public:
    
    // Constructor with an optional variable parameter
    Error(int errCode = ERR_UNDEFINED, std::string message = "undefined", std::string variable = "") {
        // If variable is provided, replace %s in the message with variable
        if (!variable.empty()) {
            size_t pos = message.find("%s");
            if (pos != std::string::npos) {
                message.replace(pos, 2, variable);
            }
        }

        // Print the error message
        std::cout << ANSI_RED;
        std::cerr << "ERROR: ";
        std::cout << ANSI_RESET;
        std::cerr << message + "!\n";
        
        exit(errCode);
    }
};

