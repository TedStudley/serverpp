cmake_minimum_required(VERSION 2.8.4)
project(serverpp)

set (
    COMMON_SOURCE_DIR
    source/ )
set (
    COMMON_INCLUDE_DIR
    include/ )

include_directories(include/)

set ( CMAKE_CXX_FLAGS
    "--std=c++1y" )

add_executable ( server++ source/Main.cpp

    ${COMMON_SOURCE_DIR}/Socket/ServerSocket.cpp
    ${COMMON_SOURCE_DIR}/Socket/Socket.cpp

    ${COMMON_SOURCE_DIR}/Message/Message.cpp
    ${COMMON_SOURCE_DIR}/Message/HTTPRequest.cpp
    ${COMMON_SOURCE_DIR}/Message/HTTPResponse.cpp )
