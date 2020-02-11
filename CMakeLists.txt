cmake_minimum_required(VERSION 3.15)
project(gpng)

set(CMAKE_CXX_STANDARD 17)

add_executable(gpng main.cpp main.hpp)

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})
target_link_libraries(gpng ${PNG_LIBRARY})
