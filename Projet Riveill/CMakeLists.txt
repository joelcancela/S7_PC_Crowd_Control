cmake_minimum_required(VERSION 3.8)
project(Projet_Riveill)

set(CMAKE_CXX_STANDARD 11)

include_directories(libs/include)
set(SOURCE_FILES
        Entity.cpp
        Entity.h
        main.cpp
        Obstacle.cpp
        Obstacle.h
        Personne.cpp
        Personne.h
        shared_header.h
        Simulation.cpp
        Simulation.h)


add_executable(Projet_Riveill ${SOURCE_FILES})
add_custom_command(TARGET Projet_Riveill POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/redist/x86/SDL2.dll
        ${CMAKE_BINARY_DIR}/
        )
target_link_libraries(Projet_Riveill ${CMAKE_SOURCE_DIR}/redist/x86/SDL2.dll ${CMAKE_SOURCE_DIR}/redist/x86/SDL2.lib ${CMAKE_SOURCE_DIR}/redist/x86/SDL2main.lib)