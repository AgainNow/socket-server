#include <iostream>
#include <thread>

#include "SimpleServer.h"
#include "IterativeServer.h"
#include "ConcurrentServer.h"
#include "BoostAsioSimpleServer.h"

int main() {
    // SimpleServer server{};
    // IterativeServer server{};
    // ConcurrentServer server{};
    BoostAsioSimpleServer server{};

    // server.udp("127.0.0.1", 1312);
    server.tcp("127.0.0.1", 1313);
    return 0;
}