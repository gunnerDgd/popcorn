add_kernel_source(popcorn-linux-dev
    dev.h
    dev.c

    class.h
    class.c
)

target_include_directories(popcorn-linux-dev PRIVATE ../../../include)
target_include_directories(popcorn-linux-dev PRIVATE /lib/modules/${CMAKE_HOST_SYSTEM_VERSION}/build/include)