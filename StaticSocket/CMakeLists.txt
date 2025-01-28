cmake_minimum_required(VERSION 3.10)

# Add the library
add_library(StaticSocket STATIC
        src/Socket_posix.cpp
        src/Socket_windows.cpp
        src/Socket_common.cpp
        include/Socket_posix.h
)

if(WIN32)
    # Add the Windows-specific socket implementation
    target_sources(StaticSocket PRIVATE src/Socket_windows.cpp)
    # Link the WinSock2 library publicly to propagate to dependents
    target_link_libraries(StaticSocket PUBLIC ws2_32)
else()
    # Add the POSIX-specific socket implementation
    target_sources(StaticSocket PRIVATE src/Socket_posix.cpp)
endif()

# Include header files for library consumers
target_include_directories(StaticSocket PUBLIC include)


