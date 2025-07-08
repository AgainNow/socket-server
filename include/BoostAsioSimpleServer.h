#pragma once

#include <cstdint>

class BoostAsioSimpleServer {
public:
    void tcp(const char* ip_addr, uint16_t port);
};
