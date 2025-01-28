cmake_minimum_required(VERSION 3.10)

# Add the executable
add_executable(Server
        src/Server.cpp
        src/Server.h
)
# Link the StaticSocket library
target_link_libraries(Server PRIVATE StaticSocket)