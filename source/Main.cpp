#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <Socket/ServerSocket.hpp>
#include <Message/HTTPRequest.hpp>
#include <Message/HTTPResponse.hpp>
#include <Servlet/TestServlet.hpp>

std::map<std::string, Servlet&> ServletManager::_servletRegistry = std::map<std::string, Servlet&>();

int main() {
    ServerSocket serverSock = ServerSocket();
    ServletManager manager;
    try {
        serverSock.bind(5009);
        serverSock.listen();
        while(true) {
            ServerSocket connectionSock = serverSock.accept();

            std::string message = connectionSock.receive();
            int processID = fork();
            if (processID == 0) {
                // this is the parent process
                connectionSock.close();
            } else {
                HTTPRequest request = HTTPRequest().fromString(message);

                HTTPResponse response = manager.get("TetServlet").handleRequest(request);

                connectionSock.send(response.toString());
                connectionSock.close();
            }
        }
    } catch (std::exception &e) {
        serverSock.close();
        std::cout << "Caught terminal exception : " << e.what() << std::endl;
        return 1;
    }
}

