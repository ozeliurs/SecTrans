cmake_minimum_required(VERSION 3.18)
project(SecTrans)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenSSL REQUIRED)

add_executable(SecTransServer
        src/server/server.cpp
        src/server/SecTransServer.cpp
        src/server/SecTransServer.h
        src/lib/client.h
        src/lib/server.h
        src/lib/ultimateClient.h
        src/lib/ultimateServer.h
)
target_link_libraries(SecTransServer OpenSSL::SSL ${PROJECT_SOURCE_DIR}/src/lib/libserver.so ${PROJECT_SOURCE_DIR}/src/lib/libclient.so)

add_executable(SecTransClient
        src/client/client.cpp
        src/client/SecTransClient.cpp
        src/client/SecTransClient.h
        src/lib/client.h
        src/lib/server.h
        src/lib/ultimateClient.h
        src/lib/ultimateServer.h
)
target_link_libraries(SecTransClient OpenSSL::SSL ${PROJECT_SOURCE_DIR}/src/lib/libserver.so ${PROJECT_SOURCE_DIR}/src/lib/libclient.so)