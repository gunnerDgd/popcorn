cmake_minimum_required(VERSION 3.12)
project(popcorn)

if   (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    if    (NOT EXISTS ${CMAKE_SOURCE_DIR}/lib)
        file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
    endif ()
    execute_process(COMMAND git clone https://github.com/gunnerDgd/klever WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
    include        (${CMAKE_SOURCE_DIR}/lib/klever/klever.cmake)
endif()

add_kernel_module    (popcorn)
kernel_module_include(popcorn ${CMAKE_CURRENT_SOURCE_DIR}/include)
if     (KLEVER_ARCH STREQUAL "x86_64")
    add_compile_definitions(PRESET_ARCH_X86_64)
    add_compile_definitions(PRESET_ARCH_BIT=64)
    kernel_module_define   (popcorn
        PRESET_ARCH_X86_64
        PRESET_ARCH_BIT=64
        PRESET_LINUX
    )
endif()

add_subdirectory(include)
add_subdirectory(src)

if   (UNIX AND NOT APPLE)
    add_compile_definitions(PRESET_LINUX)
    add_subdirectory       (linux)
endif()

if   (DEFINED PO_TARGET_KERNEL_MAJOR AND DEFINED PO_TARGET_KERNEL_MINOR)
    add_kernel              (popcorn-kernel ${PO_TARGET_KERNEL_MAJOR} ${PO_TARGET_KERNEL_MINOR})
    kernel_build            (popcorn-kernel)
    kernel_module_build     (popcorn popcorn-kernel)

    kernel_module_include   (popcorn /usr/src/${CMAKE_HOST_SYSTEM_VERSION}/include)
    kernel_module_include   (popcorn /usr/src/kernels/${CMAKE_HOST_SYSTEM_VERSION}/include)
else ()
    kernel_module_build_host(popcorn)
    kernel_module_include   (popcorn /usr/src/${CMAKE_HOST_SYSTEM_VERSION}/include)
    kernel_module_include   (popcorn /usr/src/kernels/${CMAKE_HOST_SYSTEM_VERSION}/include)
endif()

if   (PRESET_BUILD_EXAMPLE)
    add_subdirectory(example)
endif()