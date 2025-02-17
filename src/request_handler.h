/*
处理 http请求并生成响应
*/
#ifndef OWN_SERVER_REQUEST_HANDLER_H
#define OWN_SERVER_REQUEST_HANDLER_H

#include <string>
#include <boost/asio.hpp>

class RequestHandler {
public:
    void handle_request(
        const std::string& request, 
        boost::asio::ip::tcp::socket& socket
    );
};

#endif // OWN_SERVER_REQUEST_HANDLER_H