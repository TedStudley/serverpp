#pragma once

#include <string>
#include <stdexcept>

class SocketException : public std::runtime_error {
  public:
    SocketException(const std::string& message) : std::runtime_error(message) {};

    const char* what() const noexcept {
      return "Testing\n";
    }


};
