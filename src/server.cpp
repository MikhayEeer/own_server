#include "server.h"
#include <iostream>

Server::Server(u_short port)
    : acceptor_(io_context_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
      thread_pool_(std::thread::hardware_concurrency()) {
} // 通过成员初始化列表来初始化成员函数
// 构造函数的函数体是空的

void Server::start(){
    thread_pool_.start();

    accept_connection();

    io_context_.run();
}

void Server::accept_connection() {
    auto connection = std::make_shared<Connection>(io_context_, request_handler_);
    acceptor_.async_accept(connection->socket(),
                           [this, connection](const boost::system::error_code& error) {
                               if (!error) {
                                   // 分配给线程池处理
                                   thread_pool_.enqueue([connection]() { connection->start(); });
                               }
                               accept_connection();
                           });
}