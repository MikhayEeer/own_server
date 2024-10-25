#include "request_handler.h"
#include <iostream>

void RequestHandler::handle_request(const std::string& request, boost::asio::ip::tcp::socket& socket) {
    std::cout<< "Request received : " << request <<std::endl;
    std::cout << "Handling request on socket " << socket.remote_endpoint() << std::endl;

    std::string response_body = "Hello, This is a web server test.";
    std::ostringstream response_stream;
    response_stream << "HTTP/1.1 200 OK \r\n"
                    << "Content-Length: " << response_body.size() << "\r\n"
                    << "Content-Type: text/plain; charset=utf-8\r\n"
                    << "\r\n"
                    << response_body;
    std::string response = response_stream.str();

    boost::asio::write(socket, boost::asio::buffer(response));
    std::cout << "Response sent to " << socket.remote_endpoint() << std::endl<<"=-=-=-="<<std::endl;
}