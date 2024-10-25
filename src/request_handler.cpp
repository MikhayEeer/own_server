#include "request_handler.h"
#include <iostream>

void RequestHandler::handle_request(const std::string& request, boost::asio::ip::tcp::socket& socket) {
    std::cout<< "Request received : " << request <<std::endl;

    std::string response = "HTTP:/1.1 200 OK\r\nContent-Length: 12\r\n\nHello, World!";
    boost::asio::write(socket, boost::asio::buffer(response));
}