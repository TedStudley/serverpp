#pragma once

#include <Servlet/Servlet.hpp>

class TestServlet : public Servlet {
public:
    virtual HTTPResponse handleRequest(HTTPRequest& request);
protected:
};
