cmake_minimum_required(VERSION 3.22)
project(SDIZO2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(SDIZO2
        Testing.h
        Graphs.cpp
        Graphs.h
        List.cpp
        List.h
        Matrix.cpp
        Matrix.h
        pch.h
        SDIZO2.cpp
        Tests.cpp
        Tests.h Menu.cpp Menu.h Testing.cpp)
