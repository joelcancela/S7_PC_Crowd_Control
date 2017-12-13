cmake_minimum_required(VERSION 3.8)
project(Projet_Riveill)

set(CMAKE_CXX_STANDARD 11)
add_definitions(-DW_UI)
set(SOURCE_FILES
        Command.cpp
        Command.h
        Datagrid.h
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
if (UNIX)#sudo apt-get install libsdl2-dev
    add_definitions(-DW_UI)
    INCLUDE(FindPkgConfig)
    PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
    INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
endif ()
add_executable(Projet_Riveill ${SOURCE_FILES})
if (UNIX)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES})
endif ()
find_package(Threads REQUIRED)
if (THREADS_HAVE_PTHREAD_ARG)
    set_property(TARGET Projet_Riveill PROPERTY COMPILE_OPTIONS "-pthread")
    set_property(TARGET Projet_Riveill PROPERTY INTERFACE_COMPILE_OPTIONS "-pthread")
endif ()
if (CMAKE_THREAD_LIBS_INIT)
    target_link_libraries(Projet_Riveill "${CMAKE_THREAD_LIBS_INIT}")
endif ()
