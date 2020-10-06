// Definition of Error Class

#include <vector>
#include <iostream>

enum ErrorType {
    None,
    SetSocketAddrError,
    BindError,
    ListenError,
    ConnectError,
    AcceptError,
    SocketReadError,
    SocketWriteError,
    SocketCloseError,
};

class Error
{
private:
    std::vector<ErrorType> error_types;
public:
    Error();
    ~Error();
    void check(ErrorType etype);
};

