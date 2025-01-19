/*
管理服务器的生命周期
包括监听端口 接受连接 启动线程池
*/
#include "server.h"
#include <iostream>
#include <functional>

Server::Server(un_short port)
    : acceptor_(io_context_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
      thread_pool_(std::thread::hardware_concurrency()) {
        std::cout<< "Start to listen port: "<<port<<std::endl;
} // 通过成员初始化列表来初始化成员函数
// 构造函数的函数体是空的

void Server::start(){
    thread_pool_.start();

    accept_connection();

    io_context_.run();
}

void Server::accept_connection() {
    auto connection = std::make_shared<Connection>(io_context_, request_handler_);

    // 使用 std::bind 创建回调函数
    acceptor_.async_accept(connection->socket(), std::bind(&Server::handle_accept, this, connection, std::placeholders::_1));
}

void Server::handle_accept(std::shared_ptr<Connection> connection, const boost::system::error_code& error) {
    if (!error) {
        // 将连接分配给线程池处理
        thread_pool_.enqueue(std::bind(&Connection::start, connection));
    }
    // 继续接受新的连接
    accept_connection();
}