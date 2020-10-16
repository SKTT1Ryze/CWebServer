// Implementation of Server

#include "readfile.h"
#include "socket.h"
#include "prase.h"
#include "ThreadPool.h"
#include <chrono>
#include <future>

#define _BSD_SOURCE
#define config_file "./config"
int main() {
    int tp_num = 4;
    ThreadPool tpool(tp_num);
    std::vector<std::future<int>> thread_res;
    std::vector<std::string> ip_addrs = std::vector<std::string> {
    };
    std::vector<int> ports = std::vector<int> {
    };
    
    struct Config config = read_config(config_file);

    ip_addrs.push_back(config.ip_addr);
    for(int i = 0; i < config.ports.size(); i++)
        ports.push_back(config.ports[i]);
    
    for (int i = 0; i < ports.size(); i ++) {
        thread_res.emplace_back(
            tpool.enqueue([] (int i, std::string ip_address, int port) {
                std::cout << "Thread: " << i << " runing..." << std::endl;
                Socket s;
                Error e;
                char rece_message[BUFFER_SIZE];
                std::string root("/");
                std::string home("/home");
                std::string rust("/rust");
                std::string riscv("/riscv");
                std::string ref_rain("/ref_rain");
                std::string h_root(html_root);
                std::string h_home(html_home);
                std::string h_rust(html_rust);
                std::string h_riscv(html_riscv);
                std::string h_ref_rain(html_ref_rain);
                std::string h_404(html_404);
                std::vector<std::string> html_list {};
                html_list.push_back(h_root);
                html_list.push_back(h_home);
                html_list.push_back(h_rust);
                html_list.push_back(h_riscv);
                html_list.push_back(h_ref_rain);
                html_list.push_back(h_404);

                // Create a new socket
                int sockfd = s.new_socket(AF_LISTENED, SOCK_STREAM, 0);

                // Setup the host_addr structure
                e.check(s.set_addr(sockfd, AF_LISTENED, inet_addr(ip_address.c_str()), port));
                
                // Bind socket and the address structure
                e.check(s.sbind(sockfd));

                while (1)
                {
                    // Listen until accept
                    e.check(s.slisten(sockfd, MAX_BACKLOG_QUEUE));

                    int new_sockfd;
                    
                    // If get request, accept
                    e.check(s.saccept(sockfd, &new_sockfd));

                    bzero(rece_message, sizeof(rece_message));

                    // Read message
                    e.check(s.sread(new_sockfd, rece_message, sizeof(rece_message) - 1));
                    // std::cout << "Server: receive message:\n" << rece_message << std::endl;
                    std::string request = rece_message;
                    std::vector<std::string> request_prase_result = prase_request(request);
                    for (int i = 0; i < request_prase_result.size(); i++)
                        std::cout << request_prase_result[i] << std::endl;
                    
                    for (int i = 0; i < request_prase_result.size(); i++)
                        std::cout << request_prase_result[i] << std::endl;
                    
                    int render_html_index;
                    if(request_prase_result[1].compare(root) == 0) {
                        render_html_index = 0;
                    }
                    else if(request_prase_result[1].compare(home) == 0) {
                        render_html_index = 1;
                    }
                    else if(request_prase_result[1].compare(rust) == 0) {
                        render_html_index = 2;
                    }
                    else if(request_prase_result[1].compare(riscv) == 0) {
                        render_html_index = 3;
                    }
                    else if(request_prase_result[1].compare(ref_rain) == 0) {
                        render_html_index = 4;
                    }
                    else
                    {
                        render_html_index = 5;
                    }
                    std::cout << std::endl;

                    char html_context[MAX_HTML_WORD] = HTTP_HEAD;
                    read_file(html_list[render_html_index].c_str(), html_context + sizeof(HTTP_HEAD) - 1);
                    std::cout << "Read html context:\n" << html_context << std::endl;

                    // Write message
                    e.check(s.swrite(new_sockfd, html_context, sizeof(html_context)));
                }
                // Thread return
                std::cout << "Thread " << "[" << i << "]" << " return." << std::endl;
                return sockfd;
            }, i, ip_addrs[0], ports[i])
        );
    }

    for(auto && result: thread_res)
        std::cout << "Thread return: " << result.get() << std::endl;

    return 0;
}