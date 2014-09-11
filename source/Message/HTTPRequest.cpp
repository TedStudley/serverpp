#include <Message/HTTPRequest.hpp>

#include <boost/algorithm/string.hpp>
#include <vector>
#include <sstream>
#include <string>

// =====================================
//      HTTPRequest functions
// =====================================

std::string HTTPRequest::toString() const {
    std::stringstream requestStream;

    requestStream << _method << " " << _requestURI << " " << _httpVersion << std::endl;
    for (auto it = _headers.begin();  it != _headers.end(); ++it) {
        requestStream << it->first << ": " <<  it->second << std::endl;
    }
    if (!_content.empty()) {
        requestStream << std::endl << _content << std::endl;
    }
    return requestStream.str();
}

HTTPRequest& HTTPRequest::fromString(std::string requestString) {
    // parse the HTTP request from string
    std::vector<std::string> requestLines;
    boost::split(requestLines, requestString, boost::is_any_of("\n"));

    auto lineIt = requestLines.begin();
    std::vector<std::string> parsedLine;
    boost::split(parsedLine, (*lineIt), boost::is_any_of(" "));
    assert(parsedLine.size() == 3);

    // Parse the status line
    _method = parsedLine.at(0);
    _requestURI = parsedLine.at(1);
    _httpVersion = parsedLine.at(2);

    lineIt++;
    // Parse headers
    while ((*lineIt) != "\r" && lineIt != requestLines.end()) {
        size_t delimiterPos = lineIt->find_first_of(":");
        std::string name = lineIt->substr(0, delimiterPos);
        std::string value = lineIt->substr(delimiterPos + 1, std::string::npos);
        boost::trim(value);
        if (!_headers.count(name)) {
            _headers.emplace(name, value);
        } else {
            _headers[name] = value;
        }
        lineIt++;
    }

    if (lineIt != requestLines.end()) {
        lineIt++;
        std::stringstream contentStream;
        for (;lineIt != requestLines.end(); ++lineIt) {
            contentStream << (*lineIt);
        }
        _content = contentStream.str();
    }

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
    this->_method = method;
    return (*this);
}

HTTPRequestBuilder& HTTPRequestBuilder::setRequestURI(const std::string requestURI) {
    this->_requestURI = requestURI;
    return (*this);
}

HTTPRequestBuilder&  HTTPRequestBuilder::setHTTPVersion(const std::string httpVersion) {
    this->_httpVersion = httpVersion;
    return (*this);
}

HTTPRequestBuilder& HTTPRequestBuilder::addHeader(const Header header) {
    if (!_headers.count(header.name())) {
        _headers.emplace(header.name(), header.value());
    } else {
        _headers[header.name()] = header.value();
    }
    return (*this);
}

HTTPRequestBuilder& HTTPRequestBuilder::addHeader(const std::string name, const std::string value) {
    this->addHeader(Header(name, value));
    return (*this);
}

HTTPRequestBuilder& HTTPRequestBuilder::addHeaders(const std::vector<Header> headers) {
    for (auto it = headers.begin(); it != headers.end(); ++it) {
        this->addHeader(*it);
    }
    return (*this);
}

HTTPRequestBuilder& HTTPRequestBuilder::setContent(const std::string content) {
    this->_content = content;
    return (*this);
}

HTTPRequest HTTPRequestBuilder::build() {
    return (*this);
}