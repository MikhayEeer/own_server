cmake_minimum_required(VERSION 3.10)

project(OwnServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED COMPONENTS system)
find_package(Threads REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(OwnServer
    src/main.cpp
    src/server.h
    src/server.cpp
    src/request_handler.h
    src/request_handler.cpp
    src/thread_pool.h
    src/thread_pool.cpp
    src/connection.h 
    src/connection.cpp
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/frontend/index.html
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/frontend)

target_link_libraries(OwnServer 
    ${Boost_LIBRARIES}
    Threads::Threads
)