#define ANSI_RESET "\033[0m"
#define ANSI_BOLD "\033[1m"
#define ANSI_BLUE "\033[34m"

class Arguments {
public:
    bool r;                 // Recursive desired
    bool x;                 // Reverse query
    bool _6;                // Query type AAAA instead of default A
    std::string s;         // IP/domain address
    std::string p;         // Port
    std::string address;   // Queried address

    // Constructor
    Arguments() {
        this->r = false;
        this->x = false;
        this->_6 = false;
        this->s = "";
        this->p = "53"; 
        this->address = "";
    }

    // Prints help in terminal
    void help() {
        std::cout << ANSI_BOLD << ANSI_BLUE;
        std::cout << "DNS Resolver\n";
        std::cout << ANSI_RESET << ANSI_BLUE;
        std::cout << "Usage: ./dns [-r] [-x] [-6] -s server [-p port] address\n";
        std::cout << "-r: Recursion desired (Recursion Desired = 1), otherwise no recursion.\n";
        std::cout << "-x: Reverse query instead of direct query.\n";
        std::cout << "-6: Query type AAAA instead of default A.\n";
        std::cout << "-s: IP address or domain name of the server to which the query should be sent.\n";
        std::cout << "-p: The port number to which the query should be sent, default 53.\n";
        std::cout << "address: Queried address.\n";
        std::cout << ANSI_RESET;
        exit(0);
    }

    // Parsing arguments
    void parse(int argc, char *argv[]) {   
        bool serverController = false;

        char opt;
        while((opt = getopt(argc, argv, "r::x::6::s:p:h::")) != -1) {
            switch(opt) {
                case 'r':
                    this->r = true;
                    break;
                case 'x':
                    this->x = true;
                    break;
                case '6':
                    this->_6 = true;
                    break;
                case 's':
                    this->s = optarg;
                    serverController = true;
                    break;
                case 'p':
                    this->p = optarg;
                    break;
                case 'h':
                    this->help();
                    break;
                case '?':
                    Error error("Wrong argument");
            }
        }

        if ((optind + 1) != argc) 
            Error error("Wrong number of arguments");
        if (!serverController) 
            Error error("Server argument was not given");

        this->address = argv[optind];
    }

};
