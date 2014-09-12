#include <Servlet/ServletException.hpp>
#include <Servlet/Servlet.hpp>

HTTPResponse Servlet::handleRequest(HTTPRequest &request) {
    throw new ServletException("Not implemented");
}

HTTPResponse ErrorServlet::handleRequest(HTTPRequest& request) {
    return HTTPResponseBuilder()
            .setHTTPVersion("HTTP/1.1").setStatusCode(404)
            .setReasonPhrase("Not Found")
            .setContent("<h1><b>404</b> not found</h1>").build();
}

ServletManager::ServletManager() {
    this->_errorServlet = (* new ErrorServlet);
}

ServletManager::ServletManager(std::string keyString, Servlet& servletClass) {
    this->_servletRegistry.emplace(keyString, servletClass);
}

Servlet& ServletManager::get(std::string keyString) {
    if (!this->_servletRegistry.count(keyString)) {
        return this->_errorServlet;
    }
    return this->_servletRegistry.at(keyString);
}