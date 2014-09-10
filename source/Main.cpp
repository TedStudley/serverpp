#include <iostream>
#include <Socket/SocketException.hpp>
#include <Socket/ServerSocket.hpp>
#include <Message/HTTPRequest.hpp>

int main() {
    ServerSocket serverSock;
    try {
        HTTPRequestBuilder requestBuilder;

        HTTPRequest request = requestBuilder.build();
        std::cout << request.toString() << std::endl;

        serverSock.bind(5000);


        serverSock.listen();

        ServerSocket connectionSock = serverSock.accept();
        std::string message = connectionSock.recieve();
        std::cout << message << std::endl;
        connectionSock.send("this is a test!");
        connectionSock.close();
        serverSock.close();
        return 0;
    } catch (std::exception &e) {
        serverSock.close();
        std::cout << "Caught terminal exception : " << e.what() << std::endl;
        return 1;
    }
}

