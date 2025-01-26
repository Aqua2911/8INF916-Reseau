//
// Created by grave on 2025-01-25.
//

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include "Socket.h"

class SocketWindows : public Socket {
private:
    SOCKET sock;
public:
    SocketWindows() : sock(INVALID_SOCKET) {
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);
    }

    ~SocketWindows() {
        closesocket(sock);
        WSACleanup();
    }

    bool openSocket() override {
        sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        return sock != INVALID_SOCKET;
    }

    bool sendTo(const std::string& address, const std::string& message) override {
        sockaddr_in destAddr = {};
        destAddr.sin_family = AF_INET;
        destAddr.sin_port = htons(5555);
        inet_pton(AF_INET, address.c_str(), &destAddr.sin_addr);

        int sendResult = sendto(sock, message.c_str(), message.size(), 0, (sockaddr*)&destAddr, sizeof(destAddr));
        return sendResult != SOCKET_ERROR;
    }

    std::string receiveFrom() override {
        sockaddr_in sourceAddr;
        int addrLen = sizeof(sourceAddr);
        char buffer[1024];
        int recvResult = recvfrom(sock, buffer, sizeof(buffer), 0, (sockaddr*)&sourceAddr, &addrLen);
        if (recvResult > 0) {
            return std::string(buffer, recvResult);
        }
        return "";
    }

    void closeSocket() override {
        closesocket(sock);
    }
};
#endif // _WIN32