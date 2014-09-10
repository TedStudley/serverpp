#pragma once

#include <string>

#include "Socket/Socket.hpp"

class ServerSocket : public Socket {
  public:
    ServerSocket& listen();

    ServerSocket& accept();

    ServerSocket& send(std::string message);

    std::string recieve();

  protected:
    int _connectionLimit = 50;
};
