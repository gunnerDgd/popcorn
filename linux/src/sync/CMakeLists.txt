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
file(RELATIVE_PATH popcorn-sync-path ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(popcorn-sync PROPERTIES MODULE_PATH ${popcorn-sync-path})