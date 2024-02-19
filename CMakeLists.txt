cmake_minimum_required(VERSION 3.12)
project(popcorn)
set    (popcorn-dir ${CMAKE_CURRENT_SOURCE_DIR})
include(build/define.cmake)
include(build/module.cmake)

arch_define       ()
compiler_define   ()
environment_define()

add_subdirectory(include)
add_subdirectory(src)
if    (UNIX AND NOT APPLE)
    add_subdirectory(linux)
endif ()

add_subdirectory(example)
