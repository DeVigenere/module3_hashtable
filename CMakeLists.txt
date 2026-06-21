cmake_minimum_required(VERSION 3.10)
project(HashTable)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
add_executable(hash_table src/main.cpp)