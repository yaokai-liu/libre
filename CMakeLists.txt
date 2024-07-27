cmake_minimum_required(VERSION 3.28)
project(libre C)

set(CMAKE_C_STANDARD 23)
add_compile_options("-msse4" "-mavx2" "-O3")
add_compile_definitions("INLINE=inline")
include_directories(.)
add_library(re STATIC libre.c libre.h)

add_executable(test test/main.c)
target_link_libraries(test PRIVATE re)
