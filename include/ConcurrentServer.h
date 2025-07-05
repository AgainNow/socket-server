// 基于系统调用的并发socket服务端
#include <cstdint>
#include <sys/socket.h>

class ConcurrentServer {
public:
    void udp(const char* ip_addr = "127.0.0.1", uint16_t port = 1312);
    void tcp(const char* ip_addr = "127.0.0.1", uint16_t port = 1312);

private:
    static void udp_handle(int sd, char* request, int len, sockaddr* cliaddr, socklen_t cliaddr_len);
    static void tcp_handle(int nsd);
};