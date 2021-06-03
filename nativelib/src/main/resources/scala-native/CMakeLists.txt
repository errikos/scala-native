cmake_minimum_required(VERSION 3.19)
project(nativelib)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

add_compile_options(-DREACTIVE_ISOLATES)

add_subdirectory(gc)
add_subdirectory(isolates)

add_dependencies(isolates
        immix-isolates)