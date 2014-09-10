#include "Socket/SocketException.hpp"
#include "Socket/Socket.hpp"

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cerrno>

Socket::Socket() {
  memset(&_sockAddr, 0, sizeof(_sockAddr));
  if ((this->_sockFD = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
    throw SocketException(strerror(errno));
  }

  int optval = 1;
  if (setsockopt(this->_sockFD, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1) {
    throw SocketException(strerror(errno));
  }
  std::cout << "Created socket " << _sockFD << std::endl;
}

Socket::Socket(const int sockFD) : Socket() {
  memset(&_sockAddr, 0, sizeof(_sockAddr));
  this->_sockFD = sockFD;
  std::cout << "Copied socket " << _sockFD << std::endl;
}

Socket& Socket::bind(const int port) {
  if (::bind(this->_sockFD, (struct sockaddr *) &_sockAddr, sizeof(_sockAddr)) == -1) {
    throw SocketException(strerror(errno));
  }
  std::cout << "Bound socket " << _sockFD << " to port " << port << std::endl;
  return (*this);
}

Socket& Socket::close() {
  if (::close(_sockFD) == -1) {
    throw SocketException(strerror(errno));
  }
  std::cout << "Closed socket " << _sockFD << std::endl;
  return (*this);
}
