/************************************************************
* Project:     	DNS resolver								*
* File:        	DnsResponseReceiber.cpp						*
* Date:        	14.11.2023									*
* Author: 		Adam Ližičiar <xlizic00@stud.fit.vutbr.cz>	*
*************************************************************/	

#include <iostream>
#include <cstring>
#include <cstdint>
#include <arpa/inet.h>

/*
 *  Class for parsing response from DNS server
 */
class DnsResponseReceiver {
    public:
    void    parse(char *responseOfDns, int *dnsResponseSize);

    private:
    void    check_for_root_label(char *&startingPoint);
    bool    handle_pointer_in_label(char *&startingPoint, bool canBePointer, char *startingPointOfDns, bool &startingPointWasUsed, char *&tmpStartingPoint);
    void    process_standard_label(char *&startingPoint);
    char*   parse_response_label(char *startingPoint, bool canBePointer, char *startingPointOfDns);
    char*   parse_aaa_label(char *responseAnswerPtr, int numOfAnswers, char *responseOfDns);
    char*   parseDnsRecord(char* dnsRecordPointer, tDnsAnswer* dnsRecordHandler, char* responseOfDns);
    void    parseDnsRecordType(tDnsAnswer* dnsRecordHandler);
    void    parseDnsRecordClass(tDnsAnswer* dnsRecordHandler);
    char*   parseQuestions(int qdcount, char *dnsQuestionSectionData, char *responseOfDns);
    void    printHeader(tDnsHeader *dnsHeaderResponse);
};

/*
 *  Checks if the current label in the DNS response is a root label
 */ 
void DnsResponseReceiver::check_for_root_label(char *&startingPoint) {

    if (*startingPoint == 0)
        std::cout << "<root>";

}

/*
 *  Handles the pointer in a DNS label, if present
 */
bool DnsResponseReceiver::handle_pointer_in_label(char *&startingPoint, bool canBePointer, char *startingPointOfDns, bool &startingPointWasUsed, char *&tmpStartingPoint) {
    
    // Checks if the label is a pointer and handles it
    uint16_t checkCorrect;
    memcpy(&checkCorrect, startingPoint, sizeof(checkCorrect));
    checkCorrect = ntohs(checkCorrect);


    if ((checkCorrect >= (uint16_t)(0xC000)) && canBePointer) {

        // Adjust the starting point if it's a pointer
        checkCorrect -= (uint16_t)(0xC000);
        startingPoint = startingPoint + sizeof(checkCorrect);

        // Update the temporary starting point if it was not used before
        if (!startingPointWasUsed) {
            tmpStartingPoint = startingPoint;
            startingPointWasUsed = true;
        }

        startingPoint = startingPointOfDns + checkCorrect;
        
        return true;

    }

    return false;
}

/*
 *  Processes a standard DNS label (non-pointer)
 */
void DnsResponseReceiver::process_standard_label(char *&startingPoint) {
    
    // Processes a standard label by printing each character
    int8_t value = *((int8_t *)(startingPoint));

    for (int8_t index = 0; index < value; index++)
        std::cout << startingPoint[1 + index];

    // Move the starting point to the next label
    startingPoint = value + startingPoint + 1;
    std::cout << ".";

}

/*
 *  Parses the response label in the DNS response
 */
char* DnsResponseReceiver::parse_response_label(char *startingPoint, bool canBePointer, char *startingPointOfDns) {

    // Parses the response label, handling pointers and standard labels
    bool startingPointWasUsed = false;
    char *tmpStartingPoint = startingPoint;

    // Check for root label
    check_for_root_label(startingPoint);

    while (*startingPoint != 0) {

        // Handle pointer in label if present
        if (!handle_pointer_in_label(startingPoint, canBePointer, startingPointOfDns, startingPointWasUsed, tmpStartingPoint)) {

            // Process standard label
            process_standard_label(startingPoint);

        }

    }

    // Return the updated starting point
    return startingPointWasUsed ? tmpStartingPoint : startingPoint + 1;

}

/*
 *  Parser answer, authoritative and additional section
 */
char* DnsResponseReceiver::parse_aaa_label(char *responseAnswerPtr, int numOfAnswers, char *responseOfDns) {

    tDnsAnswer *dnsRecordHandler;
    
    // Iterate through answers
    for(int i = 0; i < numOfAnswers; i++) {

        std::cout << "  "; 
        
        // Parse labels
        responseAnswerPtr = this->parse_response_label(responseAnswerPtr, true, responseOfDns);
        std::cout << ", ";

        // Parse the static part of Answer section
        dnsRecordHandler = (tDnsAnswer *)responseAnswerPtr;
        dnsRecordHandler->type = ntohs(dnsRecordHandler->type);
        dnsRecordHandler->class_ = ntohs(dnsRecordHandler->class_);
        dnsRecordHandler->ttl = ntohl(dnsRecordHandler->ttl);
        dnsRecordHandler->rdlength = ntohs(dnsRecordHandler->rdlength);

        // Parse record type
        parseDnsRecordType(dnsRecordHandler);

        // Parse record class
        parseDnsRecordClass(dnsRecordHandler);

        std::cout << dnsRecordHandler->ttl << ", ";

        // Parse the record
        char *dnsRecordPointer = (char *)(dnsRecordHandler) + sizeof(tDnsAnswer);
        dnsRecordPointer = parseDnsRecord(dnsRecordPointer, dnsRecordHandler, responseOfDns);

        // Move to the next answer in the DNS response.
        responseAnswerPtr = responseAnswerPtr + sizeof(tDnsAnswer) + dnsRecordHandler->rdlength;
        std::cout << "\n";
    }

    return responseAnswerPtr;
}

/*
 *  Parse DNS record type
 */
void DnsResponseReceiver::parseDnsRecordType(tDnsAnswer* dnsRecordHandler) {

    switch(dnsRecordHandler->type) {
        case A:
            std::cout << "A, ";
            break;
        case NS:
            std::cout << "NS, ";
            break;
        case MD:
            std::cout << "MD, ";
            break;
        case MF:
            std::cout << "MF, ";
            break;
        case CNAME:
            std::cout << "CNAME, ";
            break;
        case SOA:
            std::cout << "SOA, ";
            break;
        case MB:
            std::cout << "MB, ";
            break;
        case MG:
            std::cout << "MG, ";
            break;
        case MR:
            std::cout << "MR, ";
            break;
        case NULL_R:
            std::cout << "NULL";
            break;
        case WKS:
            std::cout << "WKS, ";
            break;
        case PTR:
            std::cout << "PTR, ";
            break;
        case HINFO:
            std::cout << "HINFO, ";
            break;
        case MINFO:
            std::cout << "MINFO, ";
            break;
        case MX:
            std::cout << "MX, ";
            break;
        case TXT:
            std::cout << "TXT, ";
            break;
        case SRV:
            std::cout << "SRV, ";
            break;
        case AAAA:
            std::cout << "AAAA, ";
            break;
    }

}

/*
 *  Parse DNS record class
 */
void DnsResponseReceiver::parseDnsRecordClass(tDnsAnswer* dnsRecordHandler) {

    switch(dnsRecordHandler->class_) {

        case IN:
            std::cout << "IN, ";
            break;
        case CS:
            std::cout << "CS, ";
            break;
        case CH:
            std::cout << "CH, ";
            break;
        case HS:
            std::cout << "HS, ";
            break;

    }

}

/*
 *  Parse the DNS record
 */
char* DnsResponseReceiver::parseDnsRecord(char* dnsRecordPointer, tDnsAnswer* dnsRecordHandler, char* responseOfDns) {

    switch(dnsRecordHandler->type) {

        case A:
            char ipv4[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, dnsRecordPointer, ipv4, INET_ADDRSTRLEN);
            std::cout << ipv4;
            break;
        case AAAA:
            char ipv6[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, dnsRecordPointer, ipv6, INET6_ADDRSTRLEN);
            std::cout << ipv6;
            break;
        case CNAME:
            dnsRecordPointer = this->parse_response_label(dnsRecordPointer, true, responseOfDns);
            break;
        case PTR:
            dnsRecordPointer = this->parse_response_label(dnsRecordPointer, true, responseOfDns);
            break;
        case NS:
            dnsRecordPointer = this->parse_response_label(dnsRecordPointer, true, responseOfDns);
            break;
        case SOA: {
            // parse MNAME 
            std::cout << "Primary name: ";
            dnsRecordPointer = this->parse_response_label(dnsRecordPointer, true, responseOfDns);
            std::cout << ", ";

            // parse RNAME
            std::cout << "Responsible authority mailbox: ";
            dnsRecordPointer = this->parse_response_label(dnsRecordPointer, true, responseOfDns);
            std::cout << ", ";

            // parse rest of SOA
            tSoaHeader *soaTail = (tSoaHeader *)dnsRecordPointer;
            soaTail->expire = ntohl(soaTail->expire);
            soaTail->refresh = ntohl(soaTail->refresh);
            soaTail->retry = ntohl(soaTail->retry);
            soaTail->serial = ntohl(soaTail->serial);
            soaTail->minimum = ntohl(soaTail->minimum);

            std::cout << "Serial number: " << soaTail->serial << ", ";
            std::cout << "Refresh interval: " << soaTail->refresh << ", ";
            std::cout << "Retry interval: " << soaTail->retry << ", ";
            std::cout << "Expire limit: "  << soaTail->expire << ", ";
            std::cout << "Minimum TTL: " << soaTail->minimum;
        }   break;
        case MB:
            dnsRecordPointer = this->parse_response_label(dnsRecordPointer, true, responseOfDns);
            break;
        case MD:
            dnsRecordPointer = this->parse_response_label(dnsRecordPointer, true, responseOfDns);
            break;
        case MF:
            dnsRecordPointer = this->parse_response_label(dnsRecordPointer, true, responseOfDns);
            break;
        case MG:
            dnsRecordPointer = this->parse_response_label(dnsRecordPointer, true, responseOfDns);
            break;
        case MINFO:
            // parse RMAILBX
            std::cout << "Maling list: ";
            dnsRecordPointer = this->parse_response_label(dnsRecordPointer, true, responseOfDns);
            std::cout << "Mailing errorbox: ";
            dnsRecordPointer = this->parse_response_label(dnsRecordPointer, true, responseOfDns);
            break;
        case MR:
            dnsRecordPointer = this->parse_response_label(dnsRecordPointer, true, responseOfDns);
            break;
        case MX: {
            // parse preference
            int16_t *preference = (int16_t *)dnsRecordPointer;
            std::cout << "Preference: " << ntohs(*preference);
            dnsRecordPointer = dnsRecordPointer + sizeof(int16_t);
            dnsRecordPointer = this->parse_response_label(dnsRecordPointer, true, responseOfDns);
        }   break;
        default:
            std::cout << "unsupported parsing";
            break;

    }

    return dnsRecordPointer;

}

/*
 *  Print header information
 */
void DnsResponseReceiver::printHeader(tDnsHeader *dnsHeaderResponse) {

    // Authoritative
    if(dnsHeaderResponse->aa == 1)
        std::cout << "Authoritative: Yes, ";
    else 
        std::cout << "Authoritative: No, ";

    // Recursive
    if(dnsHeaderResponse->rd == 1)
        std::cout << "Recursive: Yes, ";
    else 
        std::cout << "Recursive: No, ";

    // Truncated
    if(dnsHeaderResponse->tc == 0)
        std::cout << "Truncated: No";
    else 
        std::cout << "Truncated: Yes";

}

/*
 *  Parse and print questions
 */
char* DnsResponseReceiver::parseQuestions(int qdcount, char *dnsQuestionSectionData, char *responseOfDns) {
    
    tDnsQuestion *dnsQuestionEnd = NULL;

    for(int i = 0; i < qdcount; i++) {
        
        dnsQuestionEnd = (tDnsQuestion*)(this->parse_response_label(dnsQuestionSectionData, false, responseOfDns));
        std::cout << ", ";

        dnsQuestionEnd->qclass = ntohs(dnsQuestionEnd->qclass);
        dnsQuestionEnd->qtype = ntohs(dnsQuestionEnd->qtype);

        switch(dnsQuestionEnd->qtype) {
            case A:
                std::cout << "A, ";
                break;
            case NS:
                std::cout << "NS, ";
                break;
            case CNAME:
                std::cout << "CNAME, ";
                break;
            case SOA:
                std::cout << "SOA, ";
                break;
            case WKS:
                std::cout << "WKS, ";
                break;
            case PTR:
                std::cout << "PTR, ";
                break;
            case MX:
                std::cout << "MX, ";
                break;
            case SRV:
                std::cout << "SRV, ";
                break;
            case AAAA:
                std::cout << "AAAA, ";
                break;
            case 255:
                std::cout << "ANY, ";
                break;
        }

        switch(dnsQuestionEnd->qclass) {
            case IN:
                std::cout << "IN \n";
                break;
            case CS:
                std::cout << "CS \n";
                break;
            case CH:
                std::cout << "CH \n";
                break;
            case HS:
                std::cout << "HS \n";
                break;
        }

        dnsQuestionSectionData = ((char *)dnsQuestionEnd) + sizeof(tDnsQuestion);
    
    }

    return dnsQuestionSectionData;

}

/*
 * Main parse function
 */
void DnsResponseReceiver::parse(char *responseOfDns, int *dnsResponseSize) {

    tDnsHeader *dnsHeaderResponse = (tDnsHeader *)responseOfDns;

    dnsHeaderResponse->id = ntohs(dnsHeaderResponse->id);
    dnsHeaderResponse->qdcount = ntohs(dnsHeaderResponse->qdcount);
    dnsHeaderResponse->ancount = ntohs(dnsHeaderResponse->ancount);
    dnsHeaderResponse->nscount = ntohs(dnsHeaderResponse->nscount);
    dnsHeaderResponse->arcount = ntohs(dnsHeaderResponse->arcount);

    // Print header
    printHeader(dnsHeaderResponse);

    // Parsing the question section
    std::cout << "\n" << "Question section (" << dnsHeaderResponse->qdcount << ")\n";
    std::cout << "  "; 
    char *dnsQuestionSectionData = ((char *)dnsHeaderResponse) + sizeof(tDnsHeader);
    dnsQuestionSectionData = parseQuestions(dnsHeaderResponse->qdcount, dnsQuestionSectionData, responseOfDns);

    // Parsing Answer, Authority, and Additional sections
    std::cout << "Answer section (" << dnsHeaderResponse->ancount << ") \n";
    char *responseAnswerPtr = dnsQuestionSectionData;
    responseAnswerPtr = this->parse_aaa_label(responseAnswerPtr, dnsHeaderResponse->ancount, responseOfDns);

    std::cout << "Authority section (" << dnsHeaderResponse->nscount << ") \n";
    responseAnswerPtr = this->parse_aaa_label(responseAnswerPtr, dnsHeaderResponse->nscount, responseOfDns);

    std::cout << "Additional section (" << dnsHeaderResponse->arcount << ") \n";
    responseAnswerPtr = this->parse_aaa_label(responseAnswerPtr, dnsHeaderResponse->arcount, responseOfDns);

}
