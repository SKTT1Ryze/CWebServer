// Implementation of Server

#include "read_html.h"
#include "socket.h"
#include "request_prase.h"

#define _BSD_SOURCE

int main() {
    Error e;
    Socket s;
    char rece_message[BUFFER_SIZE];
    char html_context[MAX_HTML_WORD] = HTTP_HEAD;
    std::vector<std::string> html_list {};
    std::string h_root(html_root);
    std::string h_home(html_home);
    std::string h_rust(html_rust);
    std::string h_riscv(html_riscv);
    std::string h_404(html_404);
    html_list.push_back(h_root);
    html_list.push_back(h_home);
    html_list.push_back(h_rust);
    html_list.push_back(h_riscv);
    html_list.push_back(h_404);
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

    bzero(rece_message, sizeof(rece_message));
    
    // Read message
    e.check(s.sread(sockfd_id_2, rece_message, sizeof(rece_message) - 1));
    // std::cout << "Server: receive message:\n" << rece_message << std::endl;
    std::string request = rece_message;
    std::vector<std::string> request_prase_result = prase_request(request);

    for (int i = 0; i < request_prase_result.size(); i++)
        std::cout << request_prase_result[i] << std::endl;
    std::string root("/");
    std::string home("/home");
    std::string rust("/rust");
    std::string riscv("/riscv");

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
    else
    {
        render_html_index = 4;
    }
    
    std::cout << std::endl;

    read_html(html_list[render_html_index].c_str(), html_context + sizeof(HTTP_HEAD) - 1);

    std::cout << "Read html context:\n" << html_context << std::endl;

    // Write response
    e.check(s.swrite(sockfd_id_2, html_context, strlen(html_context)));

    return 0;
}