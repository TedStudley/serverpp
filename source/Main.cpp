#include <iostream>
#include <Socket/SocketException.hpp>
#include <Socket/ServerSocket.hpp>
#include <Message/HTTPRequest.hpp>
#include <Message/HTTPResponse.hpp>

int main() {
    ServerSocket serverSock = ServerSocket();
    try {
        serverSock.bind(5001);

        serverSock.listen();

        ServerSocket connectionSock = serverSock.accept();
        std::string message = connectionSock.receive();
        HTTPRequest request = HTTPRequest().fromString(message);

        std::cout << request.toString() << std::endl;

        HTTPResponse response = HTTPResponseBuilder()
                .setHTTPVersion("HTTP/1.1")
                .setStatusCode(400)
                .setReasonPhrase("OK")
                .setContent("test").build();

        connectionSock.send(response.toString());
        connectionSock.close();
        serverSock.close();
        return 0;
    } catch (std::exception &e) {
        serverSock.close();
        std::cout << "Caught terminal exception : " << e.what() << std::endl;
        return 1;
    }
}

