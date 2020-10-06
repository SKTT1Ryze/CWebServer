// Implementation of Socket Class


#include "socket.h"

Socket::Socket()
{
    sockfds = std::vector<int> {};
    socket_addrs = std::vector<sockaddr_in> {};
    sockfd_num = 0;
}

Socket::~Socket()
{
    for (int i = 0; i < sockfds.size(); i++)
    close(sockfds[i]);
    sockfds.clear();
    socket_addrs.clear();
    sockfd_num = 0;
}

int Socket::new_socket(int domain, int type, int protocol) {
    if (sockfd_num >= MAX_SOCKFD_NUM) {
        std::cout << "Error: too much sockfd." << std::endl;
        exit(1);
    }

    int new_sockfd;
    if ((new_sockfd = socket(domain, type, protocol)) == -1) {
        perror("Error: socket() return -1");
        exit(1);
    }
    sockfds.push_back(new_sockfd);

    sockaddr_in new_socket_addr;
    memset(&new_socket_addr, 0, sizeof(new_socket_addr));
    socket_addrs.push_back(new_socket_addr);

    sockfd_num ++;
    return sockfd_num -1;
}

ErrorType Socket::set_addr(int index, sa_family_t family, in_addr_t addr, int port) {
    if (index < 0 || index >= sockfd_num) {
        return ErrorType::SetSocketAddrError;
    }
    socket_addrs[index].sin_family = family;
    socket_addrs[index].sin_addr.s_addr = addr;
    socket_addrs[index].sin_port = htons(port);

    return ErrorType::None;
}

ErrorType Socket::sbind(int index) {
    if (index < 0 || index >= sockfd_num) return ErrorType::BindError;

    int bind_result = bind(sockfds[index], (sockaddr *)&socket_addrs[index], sizeof(socket_addrs[index]));
    
    if (bind_result < 0) return ErrorType::BindError;
    return ErrorType::None;
}

ErrorType Socket::slisten(int index, int queue_num) {
    if (index < 0 || index >= sockfd_num) return ErrorType::ListenError;

    int listen_result = listen(sockfds[index], queue_num);

    if (listen_result < 0) return ErrorType::ListenError;
    return ErrorType::None;
}

ErrorType Socket::sconnect(int index) {
    if (index < 0 || index >= sockfd_num) return ErrorType::ConnectError;
    
    int connect_result = connect(sockfds[index], (sockaddr *)&socket_addrs[index], sizeof(socket_addrs[index]));
    std::cout << "run here." << std::endl;
    if (connect_result < 0) return ErrorType::ConnectError;
    return ErrorType::None;
}

ErrorType Socket::saccept(int index, int * new_sockfd_index) {
    if (index < 0 || index >= sockfd_num) return ErrorType::AcceptError;

    sockaddr_in new_socket_addr;
    memset(&new_socket_addr, 0, sizeof(new_socket_addr));
    socklen_t new_socket_addr_len = sizeof(new_socket_addr);

    int accept_result = accept(sockfds[index], (sockaddr *)&new_socket_addr, &new_socket_addr_len);

    if (accept_result < 0) return ErrorType::AcceptError;
    sockfds.push_back(accept_result);
    socket_addrs.push_back(new_socket_addr);

    (* new_sockfd_index) = sockfd_num ++;
    std::cout << "Socket: connecting to port " << ntohs(new_socket_addr.sin_port);
    std::cout << " from address " << inet_ntoa(new_socket_addr.sin_addr) <<std::endl;
    return ErrorType::None;
}

ErrorType Socket::sread(int index, void * buf, size_t bytes) {
    if (index < 0 || index >= sockfd_num) return ErrorType::SocketReadError;

    int read_result = read(sockfds[index], buf, bytes);

    if (read_result < 0) return ErrorType::SocketReadError;
    return ErrorType::None;
}

ErrorType Socket::swrite(int index, const void * buf, size_t bytes) {
    if (index < 0 || index >= sockfd_num) return ErrorType::SocketWriteError;

    int write_result = write(sockfds[index], buf, bytes);
    if (write_result < 0) return ErrorType::SocketWriteError;
    return ErrorType::None;
}

ErrorType Socket::sclose(int index) {
    if (index < 0 || index >= sockfd_num) return ErrorType::SocketCloseError;
    close(sockfds[index]);
    return ErrorType::None;
}