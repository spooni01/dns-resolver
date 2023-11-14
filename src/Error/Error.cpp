/************************************************************
* Project:     	DNS resolver								*
* File:        	Error.cpp									*
* Date:        	20.10.2023									*
* Author: 		Adam Ližičiar <xlizic00@stud.fit.vutbr.cz>	*
*************************************************************/	

// Class will print error message and exit program 
class Error {
    public:
    
    // Constructor
    Error(std::string message) {
        std::cout << ANSI_RED;
        std::cerr << "ERROR:";
        std::cout << ANSI_RESET;
        std::cerr << message+"!\nUse './dns -h' for help.\n";
        
        exit(1);
    }  
};
