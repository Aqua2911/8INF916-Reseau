//
// Created by grave on 2025-01-25.
//

#ifndef SOCKET_H
#define SOCKET_H
#include <string>
#include <tuple>


class Socket {
  public:
    virtual ~Socket() = default;

    virtual bool openSocket() = 0;

    virtual bool bindSocket(int port) = 0;

    virtual bool sendTo(const std::string& address, const std::string& message, int port) = 0;
    virtual std::tuple<unsigned short, std::string> receiveFrom() = 0;
    virtual void closeSocket() = 0;

};



#endif //SOCKET_H
