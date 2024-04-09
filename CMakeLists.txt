cmake_minimum_required(VERSION 3.27)
project(webserv)

set(CMAKE_CXX_STANDARD 98)

add_executable(webserv srcs/main.cpp
        srcs/parsing/LocationBlock.cpp
        srcs/parsing/ServerBlock.cpp
        srcs/parsing/config.cpp
        srcs/sockets/WebServer.cpp
        srcs/sockets/DataStorage.cpp
        includes/sockets/DataStorage.hpp
        includes/Headers.hpp)
