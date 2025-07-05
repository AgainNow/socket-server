#include <iostream>

#include "SimpleServer.h"

int main() {

    SimpleServer server{};
    // server.udp("127.0.0.1", 1312);
    server.tcp("127.0.0.1", 1313);
    return 0;
}