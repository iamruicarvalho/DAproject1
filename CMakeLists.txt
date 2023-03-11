cmake_minimum_required(VERSION 3.24)
project(Projeto1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Projeto1
        main.cpp codigo/menu.cpp codigo/include/menu.h codigo/network.cpp codigo/data_structures/Graph.cpp codigo/data_structures/Heap.cpp codigo/data_structures/UFDS.cpp codigo/data_structures/VertexEdge.cpp)
