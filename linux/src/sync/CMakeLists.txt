project                 (popcorn-sync)
add_kernel_module_target(popcorn-sync
    not.h
    not.c

    mtx.h
    mtx.c

    work.h
    work.c
)

target_include_directories(popcorn-sync PRIVATE /usr/src/kernels/${CMAKE_HOST_SYSTEM_VERSION}/include)
target_include_directories(popcorn-sync PRIVATE /usr/src/linux-headers-${CMAKE_HOST_SYSTEM_VERSION}/include)
target_include_directories(popcorn-sync PRIVATE ../../../include)