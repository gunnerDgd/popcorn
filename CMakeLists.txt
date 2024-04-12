cmake_minimum_required(VERSION 3.12)
project(popcorn)

if     (NOT EXISTS ${CMAKE_SOURCE_DIR}/lib/klever)
    if   (NOT EXISTS "/usr/bin/git")
        if    (EXISTS "/usr/bin/dnf")
            execute_process(COMMAND sudo -S dnf install -y git)
        elseif(EXISTS "/usr/bin/apt")
            execute_process(COMMAND sudo -S apt-get install -y git)
        endif ()
    endif()

    if    (NOT EXISTS ${CMAKE_SOURCE_DIR}/lib)
        file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
    endif ()
    execute_process(COMMAND git clone https://github.com/gunnerDgd/klever WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
endif()

if   (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    include (${CMAKE_SOURCE_DIR}/lib/klever/klever.cmake)
endif()

if     (KLEVER_ARCH STREQUAL "x86_64")
    add_compile_definitions(PRESET_ARCH_X86_64)
    add_compile_definitions(PRESET_ARCH_BIT=64)
endif()

if   (UNIX AND NOT APPLE)
    add_compile_definitions(PRESET_LINUX)
endif()

add_subdirectory(src)
add_subdirectory(include)

add_kernel_module    (popcorn)
kernel_module_source (popcorn popcorn-core popcorn-collections)
kernel_module_include(popcorn ${CMAKE_CURRENT_SOURCE_DIR}/include)

if   (UNIX AND NOT APPLE)
    add_subdirectory    (linux)
    kernel_module_source(popcorn
        popcorn-linux-thread
        popcorn-linux-dev
        popcorn-linux-fs
    )

    kernel_module_include(popcorn ${CMAKE_CURRENT_SOURCE_DIR}/linux/include)
endif()

kernel_module_build_host(popcorn popcorn)
kernel_module_define    (popcorn
        PRESET_ARCH_X86_64
        PRESET_ARCH_BIT=64
        PRESET_LINUX
)

if   (PRESET_BUILD_EXAMPLE)
    add_subdirectory(example)
endif()