//
// Created by grave on 2025-01-25.
//

#include "Server.h"
#include <iostream>
#include "Socket.h"
#include "Socket_common.cpp"

int main() {
    Socket* serverSocket = SocketCommon::createSocket();

    if (!serverSocket->openSocket()) {
        std::cerr << "Erreur lors de l'ouverture du socket." << std::endl;
        return 1;
    }

    while (true) {
        std::string message = serverSocket->receiveFrom();
        if (!message.empty()) {
            std::cout << "Message reçu: " << message << std::endl;
            serverSocket->sendTo("127.0.0.1", message); // Renvoie au même client
        }
    }

    serverSocket->closeSocket();
    return 0;
}