#include <cstdlib>
#include <cctype>
#include <cstring>
#include <iostream>
#include <unistd.h>

#include <map>
#include <string>
#include <boost/shared_ptr.hpp>

#include "download.h"
#include "http/HttpResponse.h"

int main(int argc, char* argv[]) {
    
    bool displayHeaders = false;
    std::string host;
    ushort port;
    std::string uri;
    
    char c;
    while ((c = getopt(argc, argv, "d")) != -1) {
        switch (c) {
        case 'd':
            displayHeaders = true;
        break;
        }
    }
    
    // Grab hostname
    if (optind < argc) {
        host = argv[optind++];
    } else {
        // Print usage statement, as no hostname was given.
        //std::cout << "Simple Web Client" << std::endl;
        std::cout << "Usage:" << std::endl;
        std::cout << "download [-d] hostname [port [uri]]" << std::endl;
        exit(0);
    }
    
    // Grab port
    if (optind < argc) {
        bool valid = true;
        int len = strlen(argv[optind]);
        for (int i = 0; i < len; i++) {
            if (!isdigit(argv[optind][i])) {
                valid = false;
            }
        }
        if (valid) {
            port = atoi(argv[optind]);
        } else {
            std::cout << "Invalid port entered. Assuming port 80.\n" << std::endl;
            port = 80;
        }
        optind++;
    } else {
        port = 80;
    }
    
    // Grab uir
    if (optind < argc) {
        uri = argv[optind++];
    } else {
        uri = "/";
    }
    
    
    boost::shared_ptr<http::HttpResponse> response = http::load(host, port, uri);
    
    //std::cout << "Headers:" << std::endl;
    if (response) {
        if (displayHeaders) {
            //std::cout << "Request: \n";
            std::cout << response->getRequest();
            //std::cout << "Status: " << response->getStatusCode() << " (" << response->getStatus() << ")\n" << std::endl;
            std::cout << response->getStatus() << std::endl;
            for (std::map<std::string, std::string>::const_iterator itr = response->getHeaders().begin(); itr != response->getHeaders().end(); itr++) {
                std::cout << itr->first << ": " << itr->second << "\n";
            }
            std::cout << std::endl;
        }
        
        std::cout << response->getContent() << std::endl;
    }
    
    exit(0);
}