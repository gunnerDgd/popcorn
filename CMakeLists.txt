cmake_minimum_required(VERSION 3.12)
project(popcorn)

if   (UNIX AND NOT APPLE)
    add_subdirectory(linux)
endif()

add_subdirectory(include)
add_subdirectory(src)

if   (PRESET_BUILD_EXAMPLE)
    add_subdirectory(example)
endif()