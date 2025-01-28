cmake_minimum_required(VERSION 3.10)

# Add the executable
add_executable(Client
        src/Client.cpp
        src/Client.h
)
# Link the StaticSocket library
target_link_libraries(Client PRIVATE StaticSocket)