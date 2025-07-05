#include <iostream>
#include <thread>

#include "SimpleServer.h"
#include "IterativeServer.h"
#include "ConcurrentServer.h"

int main() {
    // SimpleServer server{};
    // IterativeServer server{};
    ConcurrentServer server{};

    server.udp("127.0.0.1", 1312);
    // server.tcp("127.0.0.1", 1313);
    return 0;
}