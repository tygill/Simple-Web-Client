#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <map>
#include <string>
#include <boost/shared_ptr.hpp>

namespace http {

class HttpResponse;

// http level function that processes an HTTP request and returns the created
// HttpResponse object
boost::shared_ptr<HttpResponse> load(const std::string& host,
    ushort destPort, const std::string& uri);

class HttpResponse {
public:
    HttpResponse(const std::string& req);
    ~HttpResponse();
    
    // Request access
    std::string getRequest() const;
    
    // Status modifiers
    void setStatus(const std::string& stat);
    std::string getStatus() const;
    int getStatusCode() const;
    
    // Header manipulation functions
    bool hasHeader(const std::string& field) const;
    void addHeader(const std::string& field, const std::string& value);
    std::string getHeader(const std::string& field) const;
    const std::map<std::string, std::string>& getHeaders() const;
    
    // Content manipulations
    void setContent(const std::string& cont);
    std::string getContent() const;
    
private:
    std::string request;
    std::string status;
    int statusCode;
    std::map<std::string, std::string> header;
    std::string content;
};

}

#endif
