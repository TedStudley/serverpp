#pragma once

#include <Message/Message.hpp>
#include <utility>
#include <string>
#include <vector>
#include <map>

class HTTPRequest : public Message {
public:
    std::string toString() const;
    HTTPRequest& fromString(std::string requestString);
    std::string getMethod() const;
    std::string getRequestURI() const;

protected:
    std::string _method;
    std::string _requestURI;
};

class HTTPRequestBuilder : private HTTPRequest, public MessageBuilder {
public:
    HTTPRequestBuilder& setMethod(const std::string method);

    HTTPRequestBuilder& setRequestURI(const std::string requestURI);

    HTTPRequest build();
};