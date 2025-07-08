#include "BoostAsioSimpleServer.h"

#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

void BoostAsioSimpleServer::tcp(const char* ip_addr, uint16_t port) {
    try {
        boost::asio::io_context io;

        tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), port));
        printf("Server listening on port %d...\n", port);

        for (;;) {
            tcp::socket socket(io);
            acceptor.accept(socket);
            std::cout << "Client connected: " << socket.remote_endpoint() << "\n";

            boost::asio::streambuf buffer;
            boost::asio::read_until(socket, buffer, '\n');
            std::istream input(&buffer);
            std::string message;
            std::getline(input, message);

            std::cout << "Received: " << message << "\n";

            std::string reply = "Hello from server\n";
            boost::asio::write(socket, boost::asio::buffer(reply));
        }
    } catch (std::exception& e) {
        std::cerr << "Server error: " << e.what() << "\n";
    }
}
