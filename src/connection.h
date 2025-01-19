/*
负责处理单个客户端的连接，读取请求并调用请求处理器生成响应
*/
#ifndef OWN_SERVER_CONNECTION_H
#define OWN_SERVER_CONNECTION_H

#include "request_handler.h"
#include <boost/asio.hpp>

class Connection : public std::enable_shared_from_this<Connection>{
public:
    Connection(boost::asio::io_context& io_context, RequestHandler& request_handler);

    void start();

    boost::asio::ip::tcp::socket& socket();
private:
    void handle_read(const boost::system::error_code& error, size_t bytes_transferred);

    boost::asio::ip::tcp::socket socket_;
    RequestHandler& request_handler_;
    boost::asio::streambuf request_buffer_;

};

#endif // OWN_SERVER_CONNECTION_H