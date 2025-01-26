//
// Created by grave on 2025-01-25.
//

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