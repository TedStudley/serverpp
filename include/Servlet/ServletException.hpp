#pragma once

#include <string>
#include <stdexcept>

class ServletException : public std::runtime_error {
public:
    ServletException(const std::string& message) : std::runtime_error(message) {};
};