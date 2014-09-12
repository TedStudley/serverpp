#include <Servlet/Servlet.hpp>
#include <Servlet/TestServlet.hpp>

HTTPResponse TestServlet::handleRequest(HTTPRequest &request) {
    HTTPResponse response = HTTPResponseBuilder().setContent("hi").build();
    return response;
}

REGISTER_SERVLET(TestServlet)
