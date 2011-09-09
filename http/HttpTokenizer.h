#ifndef HTTPTOKENIZER_H
#define HTTPTOKENIZER_H

#include <string>

namespace http {

class HttpTokenizer {
public:
    enum TokenType {
        HttpStatus,
        HeaderField,
        HeaderValue,
        HeaderComplete,
        Content,
        EndOfFile,
        NoConnection
    };
    // Ownership of socketHandle is transferred to the tokenizer
    // next() is called implicitly by the constructor, so you can call
    // hasToken() right away.
    HttpTokenizer(int socketHandle);
    ~HttpTokenizer();
    
    // hasToken() will return false if the current token is EndOfFile, as that
    // really means there are no more tokens
    bool hasToken() const;
    TokenType tokenType() const;
    std::string tokenValue() const;
    void next();
    
    void setContentReserveSize(int size);
    
private:
    void next(bool firstTime);
    static std::string trim(const std::string& str);
private:
    int sock;
    TokenType currTokenType;
    std::string currTokenValue;
    // Yes, this isn't optimal in performance factors.
    // But I would have practically be reimplementing this on my own, so
    // the default implementation is probably an enhancement on that, and
    // besides - this is far from a performance critical application.
    std::string buffer;
    bool headerComplete;
    int contentReserveSize;
};

}

#endif
