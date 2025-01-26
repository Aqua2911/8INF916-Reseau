cmake_minimum_required(VERSION 3.10)
project(SocketLib)

set(CMAKE_CXX_STANDARD 20)

add_library(Socket STATIC
        src/Socket_common.cpp
        src/Socket_windows.cpp
        src/Socket_posix.cpp
)

target_include_directories(Socket PUBLIC include)