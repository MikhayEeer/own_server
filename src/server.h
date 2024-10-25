#ifndef OWN_SERVER_SERVER_H
#define OWN_SERVER_SERVER_H

#include <boost/asio.hpp>
#include <thread>

#include "request_handler.h"
#include "thread_pool.h"

class Server{
public:
    Server(u_short port);
    void start();
    void accept_connection();
private:
    typedef unsigned short u_short;

    boost::asio::io_context io_context_;  // 异步操作核心
    boost::asio::ip::tcp::acceptor acceptor_;
    ThreadPool thread_pool_; // 用于管理线程池
    RequestHandler request_handler_;
};

#endif // OWN_SERVER_SERVER_H