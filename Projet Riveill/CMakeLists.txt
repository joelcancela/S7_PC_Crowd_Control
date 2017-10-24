cmake_minimum_required(VERSION 3.8)
project(Projet_Riveill)

set(CMAKE_CXX_STANDARD 11)

include_directories(libs/include)
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


add_executable(Projet_Riveill ${SOURCE_FILES})
find_package(Threads REQUIRED)
if(THREADS_HAVE_PTHREAD_ARG)
    set_property(TARGET Projet_Riveill PROPERTY COMPILE_OPTIONS "-pthread")
    set_property(TARGET Projet_Riveill PROPERTY INTERFACE_COMPILE_OPTIONS "-pthread")
endif()
if(CMAKE_THREAD_LIBS_INIT)
    target_link_libraries(Projet_Riveill "${CMAKE_THREAD_LIBS_INIT}")
endif()

#add_custom_command(TARGET Projet_Riveill POST_BUILD
#COMMAND ${CMAKE_COMMAND} -E copy
#${CMAKE_SOURCE_DIR}/redist/x86/SDL2.dll
#${CMAKE_BINARY_DIR}/
# )
#target_link_libraries(Projet_Riveill ${CMAKE_SOURCE_DIR}/redist/x86/SDL2.dll ${CMAKE_SOURCE_DIR}/redist/x86/SDL2.lib ${CMAKE_SOURCE_DIR}/redist/x86/SDL2main.lib)