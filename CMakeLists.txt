cmake_minimum_required(VERSION 3.10)
project(Projeto1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Projeto1 main.cpp src/network.cpp src/Graph.cpp src/Heap.cpp src/UFDS.cpp src/VertexEdge.cpp src/NetworkManager.cpp src/NetworkManager.h src/Station.cpp)

