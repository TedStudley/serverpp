#include <iostream>
#include <Socket/SocketException.hpp>
#include <Socket/ServerSocket.hpp>

int main() {
  ServerSocket serverSock;
  try {
    serverSock.bind(5050);


    serverSock.listen();
    serverSock.accept();
    return 0;
  } catch (std::exception& e) {
    serverSock.close();
    std::cout << "Caught terminal exception : " << e.what() << std::endl;
    return 1;
  }
}
