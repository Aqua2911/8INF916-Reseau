//
// Created by grave on 2025-01-25.
//

#include "Client.h"

#include <iostream>
#include "Socket.h"
#ifdef _WIN32
    #include "Socket_windows.h"
#else
    #include "Socket_posix.h"
#endif

int main() {
#ifdef WIN32
    Socket* clientSocket = new SocketWindows();
#else
    Socket* clientSocket = new SocketPosix();
#endif

    if (!clientSocket->openSocket()) {
        std::cerr << "Erreur lors de l'ouverture du socket." << std::endl;
        return 1;
    }

    std::string message;
    std::cout << "Entrez un message: ";
    std::getline(std::cin, message);

    clientSocket->sendTo("127.0.0.1", message, 5555);
    std::string response = std::get<1>(clientSocket->receiveFrom());
    std::cout << "Reponse du serveur: " << response << std::endl;

    clientSocket->closeSocket();
    return 0;
};