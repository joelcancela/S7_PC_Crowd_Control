cmake_minimum_required(VERSION 3.8)
project(crowdControl)

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
if (UNIX AND NOT APPLE)#sudo apt-get install libsdl2-dev
    add_definitions(-DW_UI)
    INCLUDE(FindPkgConfig)
    PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
    INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
endif ()
add_executable(crowdControl ${SOURCE_FILES})
if (UNIX AND NOT APPLE)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES})
endif ()
find_package(Threads REQUIRED)
if (THREADS_HAVE_PTHREAD_ARG)
    set_property(TARGET crowdControl PROPERTY COMPILE_OPTIONS "-pthread")
    set_property(TARGET crowdControl PROPERTY INTERFACE_COMPILE_OPTIONS "-pthread")
endif ()
if (CMAKE_THREAD_LIBS_INIT)
    target_link_libraries(crowdControl "${CMAKE_THREAD_LIBS_INIT}")
endif ()
