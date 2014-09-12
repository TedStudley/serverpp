#pragma once

#include <Message/HTTPResponse.hpp>
#include <Message/HTTPRequest.hpp>
#include <string>
#include <map>

class Servlet {
public:
    virtual HTTPResponse handleRequest(HTTPRequest& request);

protected:
};

class ErrorServlet : public Servlet {
public:
    virtual HTTPResponse handleRequest(HTTPRequest& request);

protected:
};

class ServletManager {
public:
    ServletManager();
    ServletManager(std::string keyString, Servlet& servletEntry);
    Servlet& get(std::string keyString);

    static std::map<std::string, Servlet&> _servletRegistry;

protected:
    ErrorServlet _errorServlet;
};

#define REGISTER_SERVLET(servletClass) static ServletManager servletClass##_manager_entry(#servletClass, (* new servletClass));