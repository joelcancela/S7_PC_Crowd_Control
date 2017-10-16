cmake_minimum_required(VERSION 3.8)
project(Projet_Riveill)

set(CMAKE_CXX_STANDARD 11)
include_directories(libs/include)
include_directories(redist/x86)
link_directories(redist/x64)
set(SOURCE_FILES
        Entity.cpp
        Entity.h
        main.cpp
        main_basic.cpp
        Obstacle.cpp
        Obstacle.h
        Personne.cpp
        Personne.h
        shared_header.h
        Simulation.cpp
        Simulation.h)

add_executable(Projet_Riveill ${SOURCE_FILES})