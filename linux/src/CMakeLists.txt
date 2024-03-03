add_subdirectory (dev)
add_subdirectory (sync)
add_subdirectory (fs)

add_kernel_source(popcorn-linux
    com.h
    com.c
)

target_include_directories(popcorn-linux PRIVATE ../../include)
target_include_directories(popcorn-linux PRIVATE ${PRESET_KERNEL_HEADER})