cmake_minimum_required(VERSION 3.12)
project(popcorn)
if     (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/klever)
    if   (NOT EXISTS "/usr/bin/git")
        if    (EXISTS "/usr/bin/dnf")
            execute_process("sudo -S dnf install -y git")
        elseif(EXISTS "/usr/bin/apt")
            execute_process("sudo -S apt-get install -y git")
        endif ()
    endif()
    execute_process(COMMAND git clone https://github.com/gunnerDgd/klever WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()

set(PRESET_KERNEL_TARGET_DIR ${CMAKE_BINARY_DIR}/kernel_target)
set(PRESET_KERNEL_DIR        ${CMAKE_BINARY_DIR}/kernel)
add_subdirectory(klever)

if   (PRESET_BUILD_ARCH STREQUAL "x86_64")
    add_compile_definitions(PRESET_ARCH_X86_64)
    add_compile_definitions(PRESET_ARCH_BIT=64)
endif()

if   (UNIX AND NOT APPLE)
    add_compile_definitions(PRESET_LINUX)
endif()

add_subdirectory(src)
if   (UNIX AND NOT APPLE)
    add_subdirectory(linux)
endif()

if
add_subdirectory(example)