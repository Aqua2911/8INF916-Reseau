//
// Created by CBerl139 on 28/01/2025.
//

#ifndef SOCKET_POSIX_H
#define SOCKET_POSIX_H

#include <string>
#include <tuple>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Socket.h"

class SocketPosix final : public Socket {
public:
    int sock;

    SocketPosix() : sock(-1) {}

    ~SocketPosix() override {
        closeSocket();
    }

    bool openSocket() override;

    bool bindSocket(int port) override;

    bool sendTo(const std::string& address, const std::string& message, int port) override;

    std::tuple<unsigned short, std::string> receiveFrom() override;

    void closeSocket() override;
};

#endif // SOCKET_POSIX_H
