project          (popcorn-linux-thread)
add_kernel_source(popcorn-linux-thread
    not.h
    not.c

    work.h
    work.c
)

target_include_directories(popcorn-linux-thread PRIVATE ../../../include)
target_include_directories(popcorn-linux-thread PRIVATE /lib/modules/${CMAKE_HOST_SYSTEM_VERSION}/build/include)