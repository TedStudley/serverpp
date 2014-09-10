#include <Socket/SocketException.hpp>
#include <Socket/ServerSocket.hpp>
#include <cerrno>

#include <iostream>

ServerSocket& ServerSocket::listen() {
    int listenResult = ::listen(this->_sockFD, this->_connectionLimit);
    if (listenResult == -1) {
        throw SocketException(strerror(errno));
    }
    std::cout << "Listening on socket " << this->_sockFD << std::endl;
    return (*this);
}

ServerSocket& ServerSocket::accept() {
    socklen_t socketSize = sizeof(this->_sockAddr);
    int acceptResult = ::accept(
            this->_sockFD,
            (sockaddr *) &(this->_sockAddr),
            &socketSize);
    if (acceptResult == -1) {
        throw new SocketException(strerror(errno));
    }
    ServerSocket& connectionSock = (* new ServerSocket);
    connectionSock._sockAddr = this->_sockAddr;
    connectionSock._sockFD = acceptResult;
    std::cout << "Accepted new connection on socket " << acceptResult << std::endl;
    return connectionSock;
}