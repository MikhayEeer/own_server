/*
入口

创建server对象，传入端口号
*/

#include <iostream>

#include "server.h"

int main(){
    try {
        Server server(8080);
        server.start();
    } catch (const std::exception& e){
        std::cerr <<"Exception: " << e.what() <<std::endl;
        return 1;
    }
    return 0;
}