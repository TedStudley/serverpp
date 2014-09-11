#include <boost/algorithm/string.hpp>
#include <sstream>

#include <Message/HTTPResponse.hpp>

/**
* HTTPResponse functions
*/
std::string HTTPResponse::toString() const {
    std::stringstream responseStream;
    responseStream << _httpVersion << " " << _statusCode << " " << _reasonPhrase << std::endl;
    for (auto it = _headers.begin();it != _headers.end(); ++it) {
        responseStream <<  it->first << ": " << it->second << std::endl;
    }
    if (!_content.empty()) {
        responseStream <<  std::endl  << _content << std::endl;
    }
    return responseStream.str();
}

HTTPResponse& HTTPResponse::fromString(const std::string responseString) {
    // Parse the HTTP Request from string
    std::vector<std::string> responseLines;
    boost::split(responseLines, responseString, boost::is_any_of("\n"));

    auto lineIt = responseLines.begin();
    std::vector<std::string> parsedLine;
    boost::split(parsedLine, (*lineIt), boost::is_any_of(" "));
    assert(parsedLine.size() == 3);

    // Parse the status line
    _httpVersion = parsedLine.at(0);
    _statusCode = atoi(parsedLine.at(1).c_str());
    _reasonPhrase = parsedLine.at(2);

    lineIt++;
    // Parse headers
    while ((*lineIt) != "\r" && lineIt != responseLines.end()) {
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

    if (lineIt != responseLines.end()) {
        lineIt++;
        std::stringstream contentStream;
        for (;lineIt != responseLines.end(); ++lineIt) {
            contentStream << (*lineIt);
        }
        _content = contentStream.str();
    }

    return (*this);
}

int HTTPResponse::getStatusCode() const {
    return _statusCode;
}

std::string HTTPResponse::getReasonPhrase() const {
    return _reasonPhrase;
}

/**
* HTTPRequest builder functions
*/

HTTPResponseBuilder& HTTPResponseBuilder::setStatusCode(int statusCode){
    this->_statusCode = statusCode;
    return (*this);
}

HTTPResponseBuilder& HTTPResponseBuilder::setReasonPhrase(std::string reasonPhrase) {
    this->_reasonPhrase = reasonPhrase;
    return (*this);
}

HTTPResponseBuilder& HTTPResponseBuilder::setHTTPVersion(const std::string httpVersion){
    this->_httpVersion = httpVersion;
    return (*this);
}

HTTPResponseBuilder& HTTPResponseBuilder::addHeader(const Header header) {
    if (!this->_headers.count(header.name())) {
        this->_headers.emplace(header.name(), header.value());
    } else {
        this->_headers[header.name()] = header.value();
    }
    return (*this);
}

HTTPResponseBuilder& HTTPResponseBuilder::addHeader(const std::string name, const std::string value) {
    this->addHeader(Header(name, value));
    return (*this);
}

HTTPResponseBuilder& HTTPResponseBuilder::addHeaders(const std::vector<Header> headers) {
    for (auto it = headers.begin(); it != headers.end(); ++it) {
        this->addHeader((*it));
    }
    return (*this);
}

HTTPResponseBuilder& HTTPResponseBuilder::setContent(const std::string content) {
    this->_content = content;
    return (*this);
}

HTTPResponse& HTTPResponseBuilder::build() {
    return (*this);
}
