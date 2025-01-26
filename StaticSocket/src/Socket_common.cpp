//
// Created by grave on 2025-01-25.
//

#include "Socket.h"
#ifdef _WIN32
    #include "Socket_windows.cpp"
#else
    #include "Socket_posix.cpp"
#endif

#ifdef _WIN32
class SocketCommon : public Socket {

    public:
      static Socket* createSocket() {

        return new SocketWindows();
    }
};

#else

class SocketCommon : public Socket {

  public:
    static Socket* createSocket() {

        return new SocketPosix();
    }
};
#endif