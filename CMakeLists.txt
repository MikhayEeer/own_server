cmake_minimum_required(VERSION 3.10)

project(OwnServer)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(OwnServer
    src/main.cpp
    src/server.h
    src/server.cpp
    src/request_handler.h
    src/request_handler.cpp
    src/thread_pool.h
    src/thread_pool.cpp
)

target_link_libraries(OwnServer ${Boost_LIBRARIES})