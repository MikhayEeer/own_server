#include "connection.h"
#include <iostream>

Connection::Connection(boost::asio::io_context& io_context, RequestHandler& request_handler)
    : socket_(io_context), request_handler_(request_handler) {}

void Connection::start() {
    boost::asio::async_read_until(socket_, request_buffer_, "\r\n\r\n",
                                  std::bind(&Connection::handle_read, shared_from_this(),
                                            std::placeholders::_1, std::placeholders::_2));
}

void Connection::handle_read(const boost::system::error_code& error, size_t bytes_transferred) {
    if (!error) {
        std::istream request_stream(&request_buffer_);
        std::string request;
        std::getline(request_stream, request);

        request_handler_.handle_request(request, socket_);
    } else {
        std::cerr << "Read error: " << error.message() << std::endl;
    }
}

boost::asio::ip::tcp::socket& Connection::socket(){
    return socket_;
}