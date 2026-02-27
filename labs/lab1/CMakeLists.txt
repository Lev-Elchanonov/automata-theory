cmake_minimum_required(VERSION 3.28)

set(CMAKE_C_COMPILER "/usr/bin/gcc-14" CACHE PATH "C compiler" FORCE)
set(CMAKE_CXX_COMPILER "/usr/bin/g++-14" CACHE PATH "C++ compiler" FORCE)

project(lab1)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(USE_SMC "Use SMC implementation for parser" OFF)


add_subdirectory(src/interfaces)
add_subdirectory(src/impls)
add_subdirectory(src/service)
add_subdirectory(src/dialogue)

add_executable(app main.cpp)

target_link_libraries(app PRIVATE
        service
        impls
        interfaces
        dialogue
)