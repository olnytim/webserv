cmake_minimum_required(VERSION 3.27)
project(webserv)

set(CMAKE_CXX_STANDARD 98)

add_executable(webserv src/main.cpp
        src/parsing/LocationBlock.cpp
        src/parsing/ServerBlock.cpp
        src/parsing/config.cpp)
