add_kernel_source(popcorn-linux-dev
    dev.h
    dev.c

    class.h
    class.c
)

target_include_directories(popcorn-linux-dev PRIVATE ../../../include)
target_include_directories(popcorn-linux-dev PRIVATE ${PRESET_KERNEL_HEADER})