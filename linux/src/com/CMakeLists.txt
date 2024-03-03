add_kernel_source(popcorn-linux-com
    com.h
    com.c

    class.h
    class.c

    bus.h
    bus.c

    dev.h
    dev.c
)

target_include_directories(popcorn-linux-com PRIVATE ../../../include)
target_include_directories(popcorn-linux-com PRIVATE ${PRESET_KERNEL_HEADER})