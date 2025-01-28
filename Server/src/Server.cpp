//
// Created by grave on 2025-01-25.
//

#include "Server.h"
#include <iostream>
#include <Socket.h>
#ifdef _WIN32
    #include "Socket_windows.h"
#else
    #include "Socket_posix.h"
#endif

int main() {
#ifdef WIN32
    Socket* serverSocket = new SocketWindows();
#else
    Socket* serverSocket = new SocketPosix();
#endif

    if (!serverSocket->openSocket()) {
        std::cerr << "Erreur lors de l'ouverture du socket." << std::endl;
        return 1;
    }

    serverSocket->bindSocket(5555);

    while (true) {
        std::tuple<u_short, std::string> data = serverSocket->receiveFrom();
        std::string message = std::get<1>(data);
        u_short port = std::get<0>(data);
        if (!message.empty()) {
            std::cout << "Message received: " << message << std::endl;
            bool success = serverSocket->sendTo("127.0.0.1", message, port);  // Send back to client
            if (success) {
                std::cout << "Message sent back to client." << std::endl;
            } else {
                std::cout << "Failed to send message back." << std::endl;
            }
        }
    }

    serverSocket->closeSocket();
    return 0;
}
