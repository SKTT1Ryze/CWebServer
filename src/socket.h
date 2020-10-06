// Definition of Socket Class

#ifndef Socket_class
#define Socket_class

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <vector>
#include "config.h"
#include "error.h"

class Socket
{
private:
    std::vector<int> sockfds;
    std::vector<sockaddr_in> socket_addrs;
public:
    int sockfd_num;
    Socket();
    ~Socket();
    int new_socket(int domain, int type, int protocol);
    ErrorType set_addr(int index, sa_family_t family, in_addr_t addr, int port); 
    ErrorType sbind(int index);
    ErrorType slisten(int index, int queue_num);
    ErrorType sconnect(int index);
    ErrorType saccept(int index, int * new_sockfd);
    ErrorType sread(int index, void * buf, size_t bytes);
    ErrorType swrite(int index, const void * buf, size_t bytes);
    ErrorType sclose(int index);
};


#endif