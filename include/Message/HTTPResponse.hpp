#pragma once

#include <Message/Message.hpp>

#include <string>

class HTTPResponse : public Message {
public:
    std::string toString() const;

    HTTPResponse &fromString(std::string requestString);

    int getStatusCode() const;

    std::string getReasonPhrase() const;

protected:
    int _statusCode;
    std::string _reasonPhrase;
};

class HTTPResponseBuilder : protected HTTPResponse {
public:
    HTTPResponseBuilder& setStatusCode(const int statusCode);

    HTTPResponseBuilder& setReasonPhrase(const std::string reasonPhrase);

    HTTPResponseBuilder& setHTTPVersion(const std::string httpVersion);

    HTTPResponseBuilder& addHeader(const Header header);
    HTTPResponseBuilder& addHeader(const std::string name, const std::string value);
    HTTPResponseBuilder& addHeaders(const std::vector<Header> headers);

    HTTPResponseBuilder& setContent(const std::string content);

    HTTPResponse& build();
};
