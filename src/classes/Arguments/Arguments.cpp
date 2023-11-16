 /************************************************************
* Project:     	DNS resolver								*
* File:        	Arguments.cpp								*
* Date:        	11.10.2023									*
* Author: 		Adam Ližičiar <xlizic00@stud.fit.vutbr.cz>	*
*************************************************************/	

/*
 *  Class to parse arguments and show help message
 */
class Arguments {
    public:
        bool                recursionDesired;  // Recursive desired
        bool                reverseQuery;      // Reverse query
        bool                ipv6;              // Query type AAAA instead of default A
        std::string         dnsServer;  // IP/domain address
        std::string         port;       // Port
        std::string         target;     // Queried address
        static Arguments*   parse_arguments(int argc, char **argv);
        static void         check_regex_of_server(Arguments *args);

    // Constructor
    Arguments() {
        this->recursionDesired  = false;
        this->reverseQuery      = false;
        this->ipv6              = false;
        this->dnsServer         = "";
        this->port              = "53"; 
        this->target            = "";
    }

    // Prints help in stdout
    void print_help() {
        std::cout << ANSI_BOLD << ANSI_BLUE;
        std::cout << "DNS Resolver\n";
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
};

/*
 *  Function will parse arguments from STDIN into `Arguments*` structure
 */ 
Arguments* Arguments::parse_arguments(int argc, char **argv) {
    Arguments *arguments = new Arguments();
    bool wasServer = false;
    char option;

    // Save options to variables
    while((option = getopt(argc, argv, "r::x::6::s:p:h::")) != -1) {
        switch(option) {
            case 'r':
                arguments->recursionDesired = true;
                break;
            case 'x':
                arguments->reverseQuery = true;
                break;
            case '6':
                arguments->ipv6 = true;
                break;
            case 's':
                arguments->dnsServer = optarg;
                wasServer = true;
                break;
            case 'p':
                arguments->port = optarg;
                break;
            case 'h':
                arguments->print_help();
                break;
            case '?':
                Error(ERR_ARG_INVALID_ARGUMENT, "invalid argument given");
        }
    }

    // Check for additional arguments
    if ((optind + 1) != argc) {
        Error(ERR_ARG_UNUSUAL_PARAMETER, "unusual parameters given");
    }
    // Check if server is missing
    else if (!wasServer) {
        Error(ERR_ARG_MISSING_SERVER, "missing `-s` argument");
    }

    arguments->target = argv[optind];

    // Check regex of server and target
    check_regex_of_server(arguments);

    return arguments;
}

/*
 *  Check if regex of server and target is correct
 */
void Arguments::check_regex_of_server(Arguments *args) {

    std::regex ipv4Pattern("^(\\d{1,3}(\\.\\d{1,3}){3})$");
    std::regex ipv6Pattern("^([0-9a-fA-F]{1,4}:){7}[0-9a-fA-F]{1,4}$");
    std::regex websitePattern("^(https?://)?(www\\.)?[-a-zA-Z0-9@:%._\\+~#=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9()@:%_\\+.~#?&//=]*)$");

    if(args->reverseQuery) {
        if(args->ipv6) {
            if(!std::regex_match(args->target, ipv6Pattern))
                Error(ERR_ARG_IS_NOT_IPV6_ADDRESS, "the target `%s` is not IPv6", args->target.c_str());
        }
        else {
            if(!std::regex_match(args->target, ipv4Pattern))
                Error(ERR_ARG_IS_NOT_IPV4_ADDRESS, "the target `%s` is not IPv4", args->target.c_str());
        }
    }
    else {
        if(!std::regex_match(args->target, websitePattern))
            Error(ERR_ARG_IS_NOT_WEBSITE, "the target `%s` is not a website url", args->target.c_str());
    }
    
}