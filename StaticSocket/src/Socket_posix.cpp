//
// Created by grave on 2025-01-25.
//

#ifndef  _WIN32
#include <iostream>
#include "Socket_posix.h"

bool SocketPosix::openSocket() {
    sock = socket(AF_INET, SOCK_DGRAM, 0); // Create a UDP socket
    return sock != -1; // Return true if the socket is valid
}

bool SocketPosix::bindSocket(int port) {
    sockaddr_in serverAddr = {};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Accept connections on any network interface
    serverAddr.sin_port = htons(port);      // Convert port number to network byte order

    // Bind the socket to the specified address and port
    return bind(sock, reinterpret_cast<sockaddr *>(&serverAddr), sizeof(serverAddr)) != -1;
}

bool SocketPosix::sendTo(const std::string& address, const std::string& message, int port) {
    sockaddr_in destAddr = {};
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(port);

    // Convert the string address to binary form
    if (inet_pton(AF_INET, address.c_str(), &destAddr.sin_addr) <= 0) {
        std::cerr << "Invalid address: " << address << std::endl;
        return false;
    }

    // Send the message to the destination address
    ssize_t sendResult = sendto(sock, message.c_str(), message.size(), 0,
                                reinterpret_cast<sockaddr *>(&destAddr), sizeof(destAddr));
    return sendResult != -1;
}

std::tuple<unsigned short, std::string> SocketPosix::receiveFrom() {
    sockaddr_in sourceAddr = {};
    socklen_t addrLen = sizeof(sourceAddr);
    char buffer[1024];
    ssize_t recvResult = recvfrom(sock, buffer, sizeof(buffer), 0, reinterpret_cast<sockaddr *>(&sourceAddr), &addrLen);

    if (recvResult > 0) {
        std::tuple<unsigned short, std::string> values(ntohs(sourceAddr.sin_port), std::string(buffer, recvResult));
        return values;
    }

    // Return an empty result in case of failure
    return {0, ""};
}

void SocketPosix::closeSocket() {
    if (sock != -1) {
        close(sock); // Close the socket
        sock = -1;
    }
}

#endif // _WIN32



/*
#ifndef _WIN32
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Socket.h"

class SocketPosix : public Socket {
private:
    int sock;
public:
    SocketPosix() : sock(-1) {}

    ~SocketPosix() {
        close(sock);
    }

    bool openSocket() override {
        sock = socket(AF_INET, SOCK_DGRAM, 0);
        return sock >= 0;
    }

    bool sendTo(const std::string& address, const std::string& message) override {
        sockaddr_in destAddr = {};
        destAddr.sin_family = AF_INET;
        destAddr.sin_port = htons(5555);
        inet_pton(AF_INET, address.c_str(), &destAddr.sin_addr);

        int sendResult = sendto(sock, message.c_str(), message.size(), 0, (sockaddr*)&destAddr, sizeof(destAddr));
        return sendResult >= 0;
    }

    std::string receiveFrom() override {
        sockaddr_in sourceAddr;
        socklen_t addrLen = sizeof(sourceAddr);
        char buffer[1024];
        int recvResult = recvfrom(sock, buffer, sizeof(buffer), 0, (sockaddr*)&sourceAddr, &addrLen);
        if (recvResult > 0) {
            return std::string(buffer, recvResult);
        }
        return "";
    }

    void closeSocket() override {
        close(sock);
    }
};
#endif // _WIN32
 */