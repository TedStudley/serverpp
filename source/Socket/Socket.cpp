#include "Socket/Socket.hpp"

#include <iostream>

Socket::Socket() {
  std::cout << "new socket" << std::endl;
}

Socket::~Socket() {
  std::cout << "removed socket" << std::endl;
}

bool Socket::isValid() const {
  if (_socketFD == -1) {
    return false;
  } else {
    return true;
  }
}
