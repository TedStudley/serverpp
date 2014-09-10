#pragma once

#include <string>

#include "Socket/Socket.hpp"

#define MAX_RECIEVE_LENGTH 256

class ServerSocket : public Socket {
  public:
    ServerSocket& listen();

    ServerSocket& accept();

    void send(const std::string message) const;

    std::string recieve() const;

  protected:
    int _connectionLimit = 50;
};
