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
    std::vector<std::string> ip_addrs = std::vector<std::string> {
        "127.0.0.1",
        "127.0.0.2",
        "127.0.0.3"
    };
    int port[3] = {6000, 7000, 8000};
    for (int i = 0; i < ip_addrs.size(); i ++) {
        thread_res.emplace_back(
            tpool.enqueue([] (int i, std::string ip_address, int port) {
                std::cout << "Thread: " << i << " runing..." << std::endl;
                Socket s;
                Error e;
                int sockfd = s.new_socket(AF_LISTENED, SOCK_STREAM, 0);

                e.check(s.set_addr(sockfd, AF_LISTENED, inet_addr(ip_address.c_str()), port));
                
                e.check(s.sbind(sockfd));

                e.check(s.slisten(sockfd, MAX_BACKLOG_QUEUE));

                int new_sockfd;
                e.check(s.saccept(sockfd, &new_sockfd));

                char buffer[BUFFER_SIZE];
                bzero(buffer, sizeof(buffer));

                e.check(s.sread(new_sockfd, buffer, sizeof(buffer) - 1));

                e.check(s.swrite(new_sockfd, buffer, sizeof(buffer)));
                std::cout << "Thread " << i << " return." << std::endl;
                return sockfd;
            }, i, ip_addrs[0], port[i])
        );
        
    }
    for(auto && result: thread_res)
        std::cout << "Thread return: " << result.get() << std::endl;

    return 0;
}