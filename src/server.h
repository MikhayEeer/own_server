#ifndef OWN_SERVER_SERVER_H
#define OWN_SERVER_SERVER_H

#include <boost/asio.hpp>
#include <thread>
#include <memory>

#include "request_handler.h"
#include "thread_pool.h"
#include "connection.h"

typedef unsigned short un_short;

class Server{
public:
    Server(un_short port);
    void start();
private:
    void accept_connection();
    void handle_accept(std::shared_ptr<Connection> connection, const boost::system::error_code& error);

    boost::asio::io_context io_context_;  // 异步操作核心
    boost::asio::ip::tcp::acceptor acceptor_;
    ThreadPool thread_pool_; // 用于管理线程池
    RequestHandler request_handler_;
};

#endif // OWN_SERVER_SERVER_H