cmake_minimum_required(VERSION 3.27)
project(SecTrans C)

set(CMAKE_C_STANDARD 23)

add_executable(SecTrans
        src/server/server.h
        src/client/client.h
        src/client/client.c
        src/server/server.c
)

target_link_libraries(SecTrans PRIVATE ${CMAKE_SOURCE_DIR}/src/client/libclient.so ${CMAKE_SOURCE_DIR}/src/server/libserver.so)
