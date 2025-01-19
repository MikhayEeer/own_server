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
        // 打印完整请求信息
        std::cout << "\n=== 接收到POST请求 ===" << std::endl;
        std::cout << "请求路径: " << path << std::endl;
        
        // 从请求体中提取消息
        size_t body_pos = request.find("\r\n\r\n");
        if (body_pos == std::string::npos) {
            std::cout << "错误: 未找到请求体" << std::endl;
            return;
        }
        
        std::string body = request.substr(body_pos + 4);
        std::cout << "请求体: " << body << std::endl;
        
        size_t msg_pos = body.find("message=");
        if (msg_pos == std::string::npos) {
            std::cout << "错误: 未找到message参数" << std::endl;
            return;
        }
        
        std::string message = body.substr(msg_pos + 8);
        std::cout << "解析到的消息: " << message << std::endl;
        
        // 准备响应内容
        std::string response_body = "{\n";
        response_body += "  \"status\": \"success\",\n";
        response_body += "  \"message\": \"服务器成功接收消息\",\n";
        response_body += "  \"receivedContent\": \"" + message + "\",\n";
        response_body += "  \"timestamp\": \"" + std::to_string(time(nullptr)) + "\"\n";
        response_body += "}";
        
        std::cout << "响应内容: " << response_body << std::endl;
        
        // 发送响应
        std::ostringstream response_stream;
        response_stream << "HTTP/1.1 200 OK\r\n"
                       << "Content-Length: " << response_body.size() << "\r\n"
                       << "Content-Type: application/json; charset=utf-8\r\n"
                       << "Access-Control-Allow-Origin: *\r\n"
                       << "\r\n"
                       << response_body;
        
        boost::asio::write(socket, boost::asio::buffer(response_stream.str()));
        std::cout << "=== 请求处理完成 ===\n" << std::endl;
    }
}