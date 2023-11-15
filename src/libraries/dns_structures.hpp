/************************************************************
* Project:     	DNS resolver								*
* File:        	src/libraries/dns_structures.hpp	    	*
* Date:        	15.11.2023									*
* Author: 		Adam Ližičiar <xlizic00@stud.fit.vutbr.cz>	*
*************************************************************/

#ifndef DNS_STRUCTURES_H
#define DNS_STRUCTURES_H

    // Sets pack() so that the compiler aligns
    // all parts of structures next to each other
    #pragma pack(push, 1)  

        typedef struct dnsHeaders {
            unsigned id :16;

            #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
                unsigned rd :1;
                unsigned tc :1;
                unsigned aa :1;
                unsigned opcode :4;
                unsigned qr :1;
                unsigned rcode :4;
                unsigned reserved :3;
                unsigned ra :1;
            #else 
                unsigned qr :1;
                unsigned opcode :4;
                unsigned aa :1;
                unsigned tc :1;
                unsigned rd :1;
                unsigned ra :1;
                unsigned reserved :3;
                unsigned rcode :4;    
            #endif


            unsigned qdcount :16;
            unsigned ancount :16;
            unsigned nscount :16;
            unsigned arcount :16;

        } tDnsHeader;
 

        typedef struct DnsQuestions {
            int qtype :16;
            int qclass :16;
            
        } tDnsQuestion;

        typedef struct DnsAnswers {
            unsigned type :16;
            unsigned class_ :16;
            unsigned ttl :32;
            unsigned rdlength :16;
        } tDnsAnswer;

        typedef struct SoaHeaders {
            uint32_t serial;
            uint32_t refresh;
            uint32_t retry;
            uint32_t expire; 
            uint32_t minimum;
        } tSoaHeader;

    #pragma pack(pop) 

#endif