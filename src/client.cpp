// Implementation of Client

#include "socket.h"
#include <netdb.h>

#define HOST_NAME "127.0.0.1"

int main(int argc, char *argv[]) {
    Error e;
    Socket s;
    char buffer[BUFFER_SIZE];
    int port = atoi(argv[1]);

    int sockfd_id = s.new_socket(AF_INET, SOCK_STREAM, 0);

    e.check(s.set_addr(sockfd_id, AF_INET, inet_addr(HOST_NAME), port));

    e.check(s.sconnect(sockfd_id));

    std::cout << "Clietn: message: ";
    bzero(buffer, sizeof(buffer));
    fgets(buffer, BUFFER_SIZE - 1, stdin);

    e.check(s.swrite(sockfd_id, buffer, sizeof(buffer)));

    bzero(buffer, sizeof(buffer));

    e.check(s.sread(sockfd_id, buffer, BUFFER_SIZE - 1));

    std::cout << "Client: receive message: " << buffer << std::endl;

    return 0;
}