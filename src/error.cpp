// Implementation of Error Class
#include "error.h"

Error::Error()
{
    error_types = std::vector<ErrorType> {};
}

Error::~Error()
{
    error_types.clear();
}

void Error::check(ErrorType etype) {
    if (etype == ErrorType::None) return;
    switch (etype)
    {
    case ErrorType::SetSocketAddrError:
        perror("Error: set socket address failed");
        // TODO
        exit(-1);
        break;
    
    case ErrorType::BindError:
        perror("Error: bind socket to an address failed");
        // TODO
        exit(-1);
        break;
    
    case ErrorType::ListenError:
        perror("Error: socket listen failed");
        // TODO
        exit(-1);
        break;
    
    case ErrorType::ConnectError:
        perror("Error: socket conncet failed");
        // TODO
        exit(-1);
        break;

    case ErrorType::AcceptError:
        perror("Error: socket accept request failed");
        // TODO
        exit(-1);
        break;
    
    case ErrorType::SocketReadError:
        perror("Error: socket read failed");
        // TODO
        exit(-1);
        break;
    
    case ErrorType::SocketWriteError:
        perror("Error: socket write failed");
        // TODO
        exit(-1);
        break;
    
    default:
        break;
    }
}

