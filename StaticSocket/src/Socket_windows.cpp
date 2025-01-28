//
// Created by grave on 2025-01-25.
//

#include <Socket.h>
#ifdef _WIN32
#include <iostream>
#include "Socket_windows.h"

bool SocketWindows::openSocket() {
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    return sock != INVALID_SOCKET;
}

bool SocketWindows::bindSocket(int port) {
    sockaddr_in serverAddr = {};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Accept connections on any network interface
    serverAddr.sin_port = htons(port);      // Convert port number to network byte order

    // Bind the socket to the specified address and port
    return bind(sock, reinterpret_cast<sockaddr *>(&serverAddr), sizeof(serverAddr)) != SOCKET_ERROR;
}

bool SocketWindows::sendTo(const std::string& address, const std::string& message, int port) {
    sockaddr_in destAddr = {};
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(port);
    inet_pton(AF_INET, address.c_str(), &destAddr.sin_addr);

    int sendResult = sendto(sock, message.c_str(), message.size(), 0, reinterpret_cast<sockaddr *>(&destAddr), sizeof(destAddr));
    return sendResult != SOCKET_ERROR;
}

std::tuple<u_short, std::string> SocketWindows::receiveFrom() {
    sockaddr_in sourceAddr= {};// Get source port
    int addrLen = sizeof(sourceAddr);
    char buffer[1024];
    int recvResult = recvfrom(sock, buffer, sizeof(buffer), 0, reinterpret_cast<sockaddr *>(&sourceAddr), &addrLen);
    if (recvResult > 0) {
        std::tuple<u_short, std::string> values(ntohs(sourceAddr.sin_port), std::string(buffer, recvResult));
        return values;
    }
    std::tuple<u_short, std::string> values(0, "");
    return values;
}

void SocketWindows::closeSocket() {
    closesocket(sock);
}
#endif // _WIN32