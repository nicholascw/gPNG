cmake_minimum_required(VERSION 3.15)
project(gpgpng)

set(CMAKE_CXX_STANDARD 17)

add_executable(gpgpng main.cpp buildinfo.h)

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})
target_link_libraries(gpgpng ${PNG_LIBRARY})