#include "ConcurrentServer.h"

#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>

void ConcurrentServer::udp_handle(int sd, char* request, int len, sockaddr* cliaddr, socklen_t cliaddr_len) {
    printf("Request: %.*s\n", len, request);
    
    char response[] = {"Get it."};
    sendto(sd, response, strlen(response), 0, cliaddr, cliaddr_len);
    
    delete[] request;
}

void ConcurrentServer::udp(const char* ip_addr, uint16_t port) {
    std::cout << __FUNCTION__ << "ing..." << std::endl;
    int sd = socket(PF_INET, SOCK_DGRAM, 0);
    
    sockaddr_in servaddr, cliaddr;
    socklen_t servaddr_len = sizeof(servaddr), cliaddr_len = sizeof(cliaddr);
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_family = PF_INET;
    servaddr.sin_port = htons(port);
    int res = bind(sd, (sockaddr*)&servaddr, servaddr_len);

    while(true) {
        char* request = new char[1024];
        auto len = recvfrom(sd, request, 1024, 0, (sockaddr*)&cliaddr, &cliaddr_len);
        
        std::thread handle{udp_handle, sd, request, len, (sockaddr*)&cliaddr, cliaddr_len};
        handle.detach();
    }
    
    close(sd);
}

void ConcurrentServer::tcp_handle(int nsd) {
    char request[1024];
    char response[1024] = {"Get it."};

    // 接收请求包
    auto len = recv(nsd, (void*)request, 1024, 0);
    printf("Request: %.*s\n", (int)len, request);
    // 发送响应包
    len = send(nsd, (const void*)response, strlen(response), 0);
    if (len == -1) {
        std::cerr << "Send failed." << std::endl;
        return;
    }
    // 关闭socket
    close(nsd);
}

void ConcurrentServer::tcp(const char* ip_addr, uint16_t port) {
    std::cout << __FUNCTION__ << "ing..." << std::endl;
    // 创建socket
    int sd = socket(PF_INET, SOCK_STREAM, 0);
    if (sd == 0) {
        std::cerr << "Create socket failed." << std::endl;
        return;
    }
    // 绑定本地端点地址
    struct sockaddr_in addr;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_family = PF_INET;
    addr.sin_port = htons(port);
    int addr_len = sizeof(addr);
    int res = bind(sd, (struct sockaddr*)&addr, addr_len);
    if (res != 0) {
        std::cerr << "Bind failed." << std::endl;
        return;
    }
    
    // 进入监听模式
    res = listen(sd, 3);
    if (res != 0) {
        std::cerr << "Listen failed." << std::endl;
        return;
    }
    
    while (true) {
        // 接收客户端连接请求（请求包）
        int nsd = accept(sd, (struct sockaddr*)&addr, (socklen_t*)&addr_len);
        if (nsd == 0) {
            std::cerr << "Accept failed." << std::endl;
            continue;
        }
        
        std::thread t{tcp_handle, nsd};
        t.detach();
    }
    
    close(sd);
}