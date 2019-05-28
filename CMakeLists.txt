cmake_minimum_required(VERSION 3.13)
project(HyperLogLog)

set(CMAKE_CXX_STANDARD 17)

add_executable(HyperLogLog main.cpp FNV.h HLL.cpp HLL.h FNV.cpp)
add_executable(TesterFNV FNV.h TesterFNV.cpp)
add_executable(TesterHLL TesterHLL.cpp HLL.h HLL.cpp FNV.h FNV.cpp)
add_executable(TesterVK TesterVK.cpp HLL.h FNV.h HLL.cpp FNV.cpp)