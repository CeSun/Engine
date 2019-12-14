cmake_minimum_required(VERSION 3.15)
project(Engine)


set(CMAKE_CXX_STANDARD 11)
include_directories(./include)
link_directories(./lib)

add_executable(Engine main.cpp)