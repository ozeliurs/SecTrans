cmake_minimum_required(VERSION 3.22)
project(SecTrans)

set(CMAKE_CXX_STANDARD 23)

find_package(OpenSSL REQUIRED)

add_executable(SecTransServer
        src/server/server.cpp

)
target_link_libraries(SecTransServer OpenSSL::SSL ${PROJECT_SOURCE_DIR}/src/lib/libserver.so ${PROJECT_SOURCE_DIR}/src/lib/libclient.so)

add_executable(SecTransClient
        src/client/client.cpp
        src/client/SecTransClient.cpp
)
target_link_libraries(SecTransClient OpenSSL::SSL ${PROJECT_SOURCE_DIR}/src/lib/libserver.so ${PROJECT_SOURCE_DIR}/src/lib/libclient.so)