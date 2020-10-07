// Implementation of Server

#include "read_html.h"
#include "socket.h"
#include "request_prase.h"
#include "ThreadPool.h"
#include <chrono>
#include <future>

#define _BSD_SOURCE

int main() {
    Error e;
    Socket s;
    ThreadPool tpool(4);
    std::vector<std::future<int>> thread_res;

    // Create a new socket
    int sockfd_id_1 = s.new_socket(AF_LISTENED, SOCK_STREAM, 0);

    // Setup the host_addr structure
    e.check(s.set_addr(sockfd_id_1, AF_LISTENED, htonl(INADDR_ANY), PORT));

    // Bind socket and the address structure
    e.check(s.sbind(sockfd_id_1));

    // Listen until accept
    e.check(s.slisten(sockfd_id_1, MAX_BACKLOG_QUEUE));

    std::vector<int> sockfd_accept = std::vector<int> {0, 0, 0, 0, 0};

    for (int i = 0; i < sockfd_accept.size(); i++) {
        thread_res.emplace_back(
            tpool.enqueue([] (int i, Socket s, Error e, int sockfd, int tsockfd) {
                // e.check(s.slisten(sockfd, MAX_BACKLOG_QUEUE));
                std::cout << "Thread: " << i << " listening..." << std::endl;
                e.check(s.saccept(sockfd, &tsockfd));
                char buffer[BUFFER_SIZE];
                bzero(buffer, sizeof(buffer));
                e.check(s.sread(tsockfd, buffer, sizeof(buffer) - 1));
                e.check(s.swrite(tsockfd, buffer, sizeof(buffer)));
                e.check(s.sclose(tsockfd));
                return tsockfd;
            },
            i, s, e, sockfd_id_1, sockfd_accept[i]
            )
        );
    }
    for(auto && result: thread_res)
        std::cout << "Thread return: " << result.get() << std::endl;
    
    std::cout << "Thread end." << std::endl;
    return 0;
}