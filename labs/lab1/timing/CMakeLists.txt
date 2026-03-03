cmake_minimum_required(VERSION 3.28)

set(CMAKE_C_COMPILER "/usr/bin/gcc-14" CACHE PATH "C compiler" FORCE)
set(CMAKE_CXX_COMPILER "/usr/bin/g++-14" CACHE PATH "C++ compiler" FORCE)

project(lab1)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(USE_SMC "Use SMC implementation for parser" OFF)




add_subdirectory(../src/interfaces ./interfaces_build)
add_subdirectory(../src/impls ./impls_build)
add_subdirectory(../src/service ./service_build)


set(LEX_VERSION_SOURCES
        ../src/impls/lex_version/source/generated.cpp
)


set(SMC_VERSION_SOURCES
        ../src/impls/smc_version/parser_sm.cpp
)


add_library(optimized_code OBJECT
        ${LEX_VERSION_SOURCES}
        ${SMC_VERSION_SOURCES}
)
target_include_directories(optimized_code PRIVATE
        ../src/impls/lex_version/include
        ../src/interfaces/include
        ../src/impls/regex_version/include
        ../src/impls/smc_version
)
target_compile_options(optimized_code PRIVATE -O2)


add_executable(timing main.cpp)
target_compile_options(timing PRIVATE -O0)

target_link_libraries(timing PRIVATE
        optimized_code
        service
        impls
        interfaces
        fl
)

target_include_directories(timing PRIVATE
        $<TARGET_PROPERTY:optimized_code,INCLUDE_DIRECTORIES>
)