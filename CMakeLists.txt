cmake_minimum_required(VERSION 3.27)
project(webserv)

set(CMAKE_CXX_STANDARD 98)

add_executable(webserv srcs/main.cpp
        srcs/parsing/LocationBlock.cpp
        srcs/parsing/ServerBlock.cpp
        srcs/parsing/config.cpp
        srcs/request/RequestParsing.cpp
        srcs/request/Request.cpp
        srcs/sockets/WebServer.cpp
        srcs/sockets/SocketListener.cpp
        srcs/sockets/DataStorage.cpp
        includes/parsing/loca.hpp
        includes/parsing/serve.hpp
        includes/parsing/cluster.hpp
        srcs/parsing/cluster.cpp
        srcs/parsing/serve.cpp
        srcs/parsing/loca.cpp
        srcs/Utils.cpp)
