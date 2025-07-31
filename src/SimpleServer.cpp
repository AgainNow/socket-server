#include "SimpleServer.h"

#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

void SimpleServer::udp(const char* ip_addr, uint16_t port) {
    std::cout << __FUNCTION__ << "ing..." << std::endl;
    int sd = socket(PF_INET, SOCK_DGRAM, 0);
    
    sockaddr_in servaddr, cliaddr;
    socklen_t servaddr_len = sizeof(servaddr), cliaddr_len = sizeof(cliaddr);
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_family = PF_INET;
    servaddr.sin_port = htons(1312);
    int res = bind(sd, (sockaddr*)&servaddr, servaddr_len);
    
    char request[1024];
    res = recvfrom(sd, request, 1024, 0, (sockaddr*)&cliaddr, &cliaddr_len);
    std::cout << "Request: " << request << std::endl;
    
    char response[] = {"Hello, I'm UDP Server."};
    sendto(sd, response, strlen(response), 0, (sockaddr*)&cliaddr, cliaddr_len);
    
    close(sd);
}

void SimpleServer::tcp(const char* ip_addr, uint16_t port) {
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
    addr.sin_port = htons(1313);
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
    // 接收客户端连接请求（请求包）
    int nsd = accept(sd, (struct sockaddr*)&addr, (socklen_t*)&addr_len);
    if (nsd == 0) {
        std::cerr << "Accept failed." << std::endl;
        return;
    }
    // 发送响应包
    char buffer[1024] = {"Hello, I'm TCP Server."};
    res = send(nsd, (const void*)buffer, 1024, 0);
    if (res == -1) {
        std::cerr << "Send failed." << std::endl;
        return;
    }
    // 关闭socket
    close(nsd);
    close(sd);
}