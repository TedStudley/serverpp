#include <Message/HTTPRequest.hpp>

#include <string>

// =====================================
//      HTTPRequest functions
// =====================================

std::string HTTPRequest::toString() const {
    return "request";
}

HTTPRequest& HTTPRequest::fromString(std::string requestString) {
    return (*this);
}

std::string HTTPRequest::getMethod() const {
    return _method;
}

std::string HTTPRequest::getRequestURI() const {
    return _requestURI;
}

// =====================================
//      HTTPRequestBuilder functions
// =====================================

HTTPRequestBuilder& HTTPRequestBuilder::setMethod(const std::string method) {
    _method = method;
    return (*this);
}

HTTPRequestBuilder& HTTPRequestBuilder::setRequestURI(const std::string requestURI) {
    _requestURI = requestURI;
    return (*this);
}

HTTPRequest HTTPRequestBuilder::build() {
    return (*this);
}