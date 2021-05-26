cmake_minimum_required(VERSION 3.19)

include_directories(shared)

add_subdirectory(shared)
add_subdirectory(immix_commix)
add_subdirectory(immix-isolates)

add_dependencies(immix-isolates
        gc-shared
        gc-immix_commix)
