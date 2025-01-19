/*
处理 http请求并生成响应
*/
#include "request_handler.h"
#include <iostream>
#include <fstream>
#include <sstream>

void RequestHandler::handle_request(const std::string& request, boost::asio::ip::tcp::socket& socket) {
    std::cout << "Request received : " << request << std::endl;
    
    // 解析请求方法和路径
    std::string method = request.substr(0, request.find(' '));
    std::string path = request.substr(request.find(' ') + 1);
    path = path.substr(0, path.find(' '));
    
    if (method == "GET") {
        // 处理GET请求，返回HTML页面
        std::ifstream file("frontend/index.html");
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string response_body = buffer.str();
        
        std::ostringstream response_stream;
        response_stream << "HTTP/1.1 200 OK\r\n"
                       << "Content-Length: " << response_body.size() << "\r\n"
                       << "Content-Type: text/html; charset=utf-8\r\n"
                       << "Access-Control-Allow-Origin: *\r\n"
                       << "\r\n"
                       << response_body;
        
        boost::asio::write(socket, boost::asio::buffer(response_stream.str()));
    }
    else if (method == "POST" && path == "/submit") {
        // 从请求体中提取消息
        size_t body_pos = request.find("\r\n\r\n");
        std::string body = request.substr(body_pos + 4);
        size_t msg_pos = body.find("message=");
        std::string message = body.substr(msg_pos + 8);
        
        // 处理消息（这里简单地返回消息）
        std::string response_body = "收到消息: " + message;
        
        std::ostringstream response_stream;
        response_stream << "HTTP/1.1 200 OK\r\n"
                       << "Content-Length: " << response_body.size() << "\r\n"
                       << "Content-Type: text/plain; charset=utf-8\r\n"
                       << "Access-Control-Allow-Origin: *\r\n"
                       << "\r\n"
                       << response_body;
        
        boost::asio::write(socket, boost::asio::buffer(response_stream.str()));
    }
}