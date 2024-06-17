cmake_minimum_required(VERSION 3.12)
project(popcorn)

add_subdirectory(include)
add_subdirectory(src)

if   (PRESET_BUILD_EXAMPLE)
    enable_busybox  (1.36.1)
    add_subdirectory(example)
endif()