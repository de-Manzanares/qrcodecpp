cmake_minimum_required(VERSION 3.28)
project(qrcode)

set(CMAKE_CXX_STANDARD 17)

add_executable(test test.cxx qrcode.cpp)

add_library(qrcode_static STATIC qrcode.cpp)
add_library(qrcode_shared SHARED qrcode.cpp)

target_link_libraries(test PUBLIC /usr/local/lib/libCatch2Maind.a /usr/local/lib/libCatch2d.a)
