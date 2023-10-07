#define ANSI_RESET "\033[0m"
#define ANSI_RED "\033[31m"

class Error {
public:
    // Constructor
    Error(std::string message) {
        std::cout << ANSI_RED;
        std::cerr << "ERROR: "+message+"!\nUse './dns -h' for help.\n";
        std::cout << ANSI_RESET;
        exit(1);
    }  
};
