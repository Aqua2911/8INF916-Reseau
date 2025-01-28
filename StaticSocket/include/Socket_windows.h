//
// Created by grave on 2025-01-26.
//

#ifndef SOCKET_WINDOWS_H
#define SOCKET_WINDOWS_H
#include <winsock2.h>
#include <ws2tcpip.h>

class SocketWindows final : public Socket {
public:
    SOCKET sock;

    SocketWindows() : sock(INVALID_SOCKET) {
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);
    }

    ~SocketWindows() override {
        closesocket(sock);
        WSACleanup();
    }

    bool openSocket() override;

    bool bindSocket(int port) override;

    bool sendTo(const std::string& address, const std::string& message, int port) override;

    std::tuple<unsigned short, std::string> receiveFrom() override;

    void closeSocket() override;
};

#endif //SOCKET_WINDOWS_H
