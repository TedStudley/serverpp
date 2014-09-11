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

class HTTPRequestBuilder : private HTTPRequest {
public:
    HTTPRequestBuilder& setMethod(const std::string method);

    HTTPRequestBuilder& setRequestURI(const std::string requestURI);

    HTTPRequestBuilder& setHTTPVersion(const std::string httpVersion);

    HTTPRequestBuilder& addHeader(const Header header);
    HTTPRequestBuilder& addHeader(const std::string name, const std::string value);
    HTTPRequestBuilder& addHeaders(const std::vector<Header> headers);

    HTTPRequestBuilder& setContent(const std::string content);

    HTTPRequest build();
};