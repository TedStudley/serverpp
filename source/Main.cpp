#include <iostream>
#include <exception>

#include "Socket/Socket.hpp"
#include "Socket/SocketException.hpp"

int main() {
  try {
    Socket socket;
    socket.isValid();

    return 0;
  } catch (std::exception& e) {
    std::cout << "caught exception" << e.what() << std::endl;
    return -1;
  }
}
