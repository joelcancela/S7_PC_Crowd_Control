cmake_minimum_required(VERSION 3.8)
project(crowdControl)

set(CMAKE_CXX_STANDARD 11)
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
if (NOT APPLE)#sudo apt-get install libsdl2-dev
    add_definitions(-DW_UI)
    set(SDL2_DIR SDL2-2.26.5/cmake)
    find_package(SDL2 REQUIRED)
endif ()
add_executable(crowdControl ${SOURCE_FILES})
if (NOT APPLE)
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
# Then copy manually all SDLs dll in cmake-build-default
