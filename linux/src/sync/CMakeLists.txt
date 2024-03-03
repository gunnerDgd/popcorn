project          (popcorn-linux-sync)
add_kernel_source(popcorn-linux-sync
    not.h
    not.c

    mtx.h
    mtx.c

    work.h
    work.c
)

target_include_directories(popcorn-linux-sync PRIVATE ../../../include)
target_include_directories(popcorn-linux-sync PRIVATE ${PRESET_KERNEL_HEADER})