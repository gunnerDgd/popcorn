project    (popcorn-sync)
add_library(popcorn-sync STATIC
    not.h
    not.c

    mtx.h
    mtx.c

    work.h
    work.c
)

target_include_directories(popcorn-sync PRIVATE ../../../include)