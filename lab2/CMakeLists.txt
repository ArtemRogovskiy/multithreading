cmake_minimum_required(VERSION 3.15)
project(multithreading)

set(CMAKE_CXX_STANDARD 14)

include_directories(/usr/include/mpi/)

#set(CMAKE_CXX_FLAGS "-Wall -Werror")

#add_executable(multithreading entrypoint.cpp parallel_jacobi.cpp)
#add_executable(multithreading jacobi_example.cpp)
add_executable(multithreading generator.cpp)