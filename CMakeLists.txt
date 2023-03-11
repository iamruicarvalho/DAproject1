cmake_minimum_required(VERSION 3.24)
project(Projeto1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Projeto1
        main.cpp src/menu.cpp src/include/menu.h src/include/station.h src/station.cpp src/network.cpp)
