cmake_minimum_required(VERSION 3.28)
project(DA2324_Proj2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(src)

add_executable(DA2324_Proj2
        src/Data.cpp
        src/Data.h
        src/Graph.cpp
        src/Graph.h
        src/Menu.cpp
        src/Menu.h
        main.cpp
        src/PQ.h
)
