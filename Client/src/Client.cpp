//
// Created by grave on 2025-01-25.
//

#include "Client.h"

#include <iostream>
#include "Socket.h"
#include "Socket_common.cpp"

int main() {
    Socket* clientSocket = SocketCommon::createSocket();
    if (!clientSocket->openSocket()) {
        std::cerr << "Erreur lors de l'ouverture du socket." << std::endl;
        return 1;
    }

    std::string message;
    std::cout << "Entrez un message: ";
    std::getline(std::cin, message);

    clientSocket->sendTo("127.0.0.1", message);
    std::string response = clientSocket->receiveFrom();
    std::cout << "Réponse du serveur: " << response << std::endl;

    clientSocket->closeSocket();
    return 0;
};