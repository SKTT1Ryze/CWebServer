// Implementation of Server

#include <fstream>
#include "socket.h"

#define _BSD_SOURCE

int main() {
    Error e;
    Socket s;
    char buffer[BUFFER_SIZE];
    char html_context[MAX_HTML_WORD] = HTTP_HEAD;
    std::ifstream read_file;

    // Create a new socket
    int sockfd_id_1 = s.new_socket(AF_INET, SOCK_STREAM, 0);

    // Setup the host_addr structure
    e.check(s.set_addr(sockfd_id_1, AF_INET, htonl(INADDR_ANY), PORT));

    // Bind socket and the address structure
    e.check(s.sbind(sockfd_id_1));

    // Listen until accept
    e.check(s.slisten(sockfd_id_1, MAX_BACKLOG_QUEUE));

    int sockfd_id_2;

    // If get request, accept
    e.check(s.saccept(sockfd_id_1, &sockfd_id_2));

    bzero(buffer, sizeof(buffer));

    // Read message
    e.check(s.sread(sockfd_id_2, buffer, sizeof(buffer) - 1));
    std::cout << "Server: receive message:\n" << buffer << std::endl;

    read_file.open(HTML, std::ios::in);
    read_file.read(html_context, 500);
    std::cout << "Read html context:\n" << html_context << std::endl;

    // Write response
    e.check(s.swrite(sockfd_id_2, html_context, strlen(html_context)));

    read_file.close();
    return 0;
}