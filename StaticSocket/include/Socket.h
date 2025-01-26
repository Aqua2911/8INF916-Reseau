//
// Created by grave on 2025-01-25.
//

#ifndef SOCKET_H
#define SOCKET_H



class Socket {
  public:
    virtual ~Socket() = default;

    virtual Socket* createSocket() = 0;

    virtual bool openSocket() = 0;
    virtual bool sendTo(const std::string& address, const std::string& message) = 0;
    virtual std::string receiveFrom() = 0;
    virtual void closeSocket() = 0;

};



#endif //SOCKET_H
