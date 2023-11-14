/************************************************************
* Project:     	DNS resolver								*
* File:        	main.cpp	    							*
* Date:        	11.10.2023									*
* Author: 		Adam Ližičiar <xlizic00@stud.fit.vutbr.cz>	*
*************************************************************/
#include "main.hpp"

/*
 *  Main function
 */
int main(int argc, char *argv[]) {
    DnsRequestSender *request = new DnsRequestSender;
    DnsResponseReceiver *response = new DnsResponseReceiver;
    int dnsResponseSize;

    // Parse arguments, send packet and parse response
    Arguments *arg = Arguments::parse_arguments(argc, argv);    	// Parse command-line arguments into an 'Arguments' object
    char *dnsResponse = request->execute(arg, &dnsResponseSize);    // Send DNS request
    response->parse(dnsResponse, &dnsResponseSize);                 // Parse DNS answer

    // Free memory
    delete[] dnsResponse;
    return 0;
}
