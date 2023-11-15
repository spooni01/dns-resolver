/************************************************************
* Project:     	DNS resolver								*
* File:        	DnsRequestSender.cpp						*
* Date:        	14.11.2023									*
* Author: 		Adam Ližičiar <xlizic00@stud.fit.vutbr.cz>	*
*************************************************************/	

/*
 *  Class for sending packet to DNS server
 */
class DnsRequestSender {
    public:
        char*                       execute(Arguments *args, int *dnsResponseSize);
    
    private:
        void                        initAddressType(struct addrinfo &addressType);
        struct addrinfo*            resolveServerAddress(const std::string &server, const std::string &port, struct addrinfo &addressType, Arguments *args);
        void                        connectToServer(int &socketHandler, struct addrinfo *resolvedAddress, Arguments *args);
        void                        setup(std::string server, std::string port, Arguments *args);
        int                         receiveResponse(char* tmpDnsResponse);
        std::vector<std::string>    splitIntoSubstrings(const std::string &str);
        std::vector<std::string>    separate(std::string originalString);
        std::vector<std::string>    processReverseIPv4(const std::string &target);
        std::vector<std::string>    processReverseIPv6(const std::string &target);
        void                        constructQuestion(tDnsHeader **header, std::vector<std::string> &substrings, int *questionPacketPosition);
        char*                       create(Arguments *args, int *packetSize);
        int                         socketHandler;
};

/*
 *  initialize address structure
 */
void DnsRequestSender::initAddressType(struct addrinfo &addressType) {

    memset(&addressType, 0, sizeof(addressType));
    addressType.ai_socktype = SOCK_DGRAM; // Using UDP protocols
    addressType.ai_family = AF_UNSPEC;    // Can be IPv4 and also IPv6

}

/*
 *  Resolve DNS server address
 */
struct addrinfo* DnsRequestSender::resolveServerAddress(const std::string &server, const std::string &port, struct addrinfo &addressType, Arguments *args) {

    struct addrinfo *resolvedAddress;

    if (getaddrinfo(server.c_str(), port.c_str(), &addressType, &resolvedAddress) != 0) {
        Error(ERR_DNS_S_UNABLE_LOAD_SERVER, "unable to load the given DNS server `%s`", args->dnsServer);
    }

    return resolvedAddress;

}

/*
 *  Connect to DNS server
 */
void DnsRequestSender::connectToServer(int &socketHandler, struct addrinfo *resolvedAddress, Arguments *args) {

    while (resolvedAddress != NULL) {

        if (resolvedAddress->ai_family == AF_INET || resolvedAddress->ai_family == AF_INET6) {

            if ((socketHandler = socket(resolvedAddress->ai_family, SOCK_DGRAM, 0)) == -1) 
                Error(ERR_DNS_S_SOCKET_WAS_NOT_CREATED, "socket was not created");
            
            if ((connect(socketHandler, resolvedAddress->ai_addr, resolvedAddress->ai_addrlen)) == -1) 
                Error(ERR_DNS_S_DNS_CONNECTION_FAILED, "unable to connect to the DNS server");
            
            break;

        }
        resolvedAddress = resolvedAddress->ai_next;

    }

    if (resolvedAddress == NULL) {
        Error(ERR_DNS_S_UNABLE_LOAD_DNS_SERVER, "unable to load the given DNS server `%s`", args->dnsServer);
    }

}

/*
 *  Function for setup
 */
void DnsRequestSender::setup(std::string server, std::string port, Arguments *args) {

    struct addrinfo addressType;
    struct addrinfo *resolvedAddress;
    struct addrinfo *tmpResolvedAddress;

    initAddressType(addressType);
    resolvedAddress = resolveServerAddress(server, port, addressType, args);
    tmpResolvedAddress = resolvedAddress;

    connectToServer(this->socketHandler, resolvedAddress, args);
    
    freeaddrinfo(tmpResolvedAddress);

}

/*
 *  Split a string into substrings
 */
std::vector<std::string> DnsRequestSender::splitIntoSubstrings(const std::string &str) {
    
    std::vector<std::string> substrings;
    std::string tmpSubstring;
    std::istringstream stream(str);

    while (std::getline(stream, tmpSubstring, ' ')) 
        substrings.push_back(tmpSubstring);

    return substrings;

}

/*
 *  Separate `originalString`
 */
std::vector<std::string> DnsRequestSender::separate(std::string originalString) {

    std::replace(originalString.begin(), originalString.end(), '.', ' ');
    return splitIntoSubstrings(originalString);

}


/*
 *  Reverse DNS query processing for IPv4
 */
std::vector<std::string> DnsRequestSender::processReverseIPv4(const std::string &target) {
    
    std::vector<std::string> substrings = this->separate(target);
    std::vector<std::string> substringsRevers;
    
    for (int i = (substrings.size() - 1); i >= 0; i--)
        substringsRevers.push_back(substrings[i]);
    
    substringsRevers.push_back("in-addr");
    substringsRevers.push_back("arpa");
    return substringsRevers;

}

/*
 *  Reverse DNS query processing for IPv6
 */
std::vector<std::string> DnsRequestSender::processReverseIPv6(const std::string &target) {
    
    std::vector<std::string> substrings;
    char tmpIPv6Address[16];
    memset(&tmpIPv6Address, 0, 16);
    inet_pton(AF_INET6, target.c_str(), &tmpIPv6Address);
    char hexByte[2];
    memset(&hexByte, 0, 2);

    for (int index = 15; index >= 0; index--) {
        char hexOne = tmpIPv6Address[index] & 0x0f;
        sprintf(hexByte, "%x", hexOne);
        substrings.push_back(hexByte);
        char hexTwo = tmpIPv6Address[index] >> 4;
        sprintf(hexByte, "%x", hexTwo);
        substrings.push_back(hexByte);
    }

    substrings.push_back("ip6");
    substrings.push_back("arpa");

    return substrings;

}

/*
 *  Construct DNS question
 */
void DnsRequestSender::constructQuestion(tDnsHeader **header, std::vector<std::string> &substrings, int *questionPacketPosition) {
    
    char *packet = (char *)(*header);
    
    for (std::size_t i = 0; i < substrings.size(); i++) {
        int len = substrings[i].length();
        *header = (tDnsHeader *)realloc(*header, (*questionPacketPosition + len + sizeof(char)));
        packet = (char *)(*header);
        memcpy((packet + *questionPacketPosition), &len, sizeof(char));
        *questionPacketPosition += sizeof(char);
        memcpy((packet + *questionPacketPosition), substrings[i].c_str(), len);
        *questionPacketPosition += len;
    }

    int tmpNum = 0;
    memcpy((packet + *questionPacketPosition), &tmpNum, sizeof(char));
    *questionPacketPosition += sizeof(char);

}

/*
 *  Create DNS packet
 */
char* DnsRequestSender::create(Arguments *args, int *packetSize) {

    std::vector<std::string> substrings;
    char tmpData[16];

    if (args->reverseQuery) {
        if (inet_pton(AF_INET, args->target.c_str(), &tmpData))
            substrings = processReverseIPv4(args->target);
        else if (inet_pton(AF_INET6, args->target.c_str(), &tmpData))
            substrings = processReverseIPv6(args->target);
        else
            Error(ERR_DNS_S_IP_ADDRESS_NOT_FOUND, "IP address of DNS server `%s` not found", args->dnsServer);
    } else {
        substrings = this->separate(args->target);
    }

    tDnsHeader *header = (tDnsHeader *)malloc(sizeof(tDnsHeader));
    memset(header, 0, sizeof(tDnsHeader));
    header->opcode = 0;
    header->id = htons(1337);
    header->rd = args->recursionDesired ? 1 : 0;
    header->qdcount = htons(1);
    int questionPacketPosition = sizeof(tDnsHeader);

    constructQuestion(&header, substrings, &questionPacketPosition);

    header = (tDnsHeader *)realloc(header, (questionPacketPosition + sizeof(tDnsQuestion)));
    tDnsQuestion *dnsQuestion = (tDnsQuestion*)((char *)header + questionPacketPosition);
    dnsQuestion->qtype = args->reverseQuery ? htons(PTR) : (args->ipv6 ? htons(AAAA) : htons(A));
    dnsQuestion->qclass = htons(IN);

    *packetSize = questionPacketPosition + sizeof(tDnsQuestion);

    return (char *)header;

}

/*
 *  Execute DNS request
 */
char* DnsRequestSender::execute(Arguments *args, int *dnsResponseSize) {

    int packetSize = 0;                                     // Size of DNS packet
    struct timeval timeCounter;                             // Time counter
    char *tmpDnsResponse = (char *)malloc(DNS_SIZE_MAXIMUM);    // Stores DNS response

    // Packet sender
    this->setup(args->dnsServer, args->port, args);     // Initialize socket
    char *packet = this->create(args, &packetSize);     // Create packet
    send(this->socketHandler, packet, packetSize, 0);   // Send packet
    free(packet);

    // Set counter
    timeCounter.tv_sec = 10; // (seconds) 
    timeCounter.tv_usec = 0; // (miliseconds)
    setsockopt(this->socketHandler, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeCounter, sizeof(timeCounter));

    // Receive response
    int sizeOfTmpDnsResponse = this->receiveResponse(tmpDnsResponse);


    close(this->socketHandler);
    *dnsResponseSize = sizeOfTmpDnsResponse;
    return (char *)realloc(tmpDnsResponse, sizeOfTmpDnsResponse + 1);

}

/*
 *  Receive the DNS response
 */
int DnsRequestSender::receiveResponse(char* tmpDnsResponse) {

    int sizeOfTmpDnsResponse = recv(this->socketHandler, tmpDnsResponse, DNS_SIZE_MAXIMUM, 0);
    if (sizeOfTmpDnsResponse < 0) {
        Error(ERR_DNS_S_RESPONSE_FAILED, "no response from DNS server");
    }

    return sizeOfTmpDnsResponse;

}

