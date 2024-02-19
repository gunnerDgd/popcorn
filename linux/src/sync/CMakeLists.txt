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
get_target_property       (popcorn-sync-src popcorn-sync SOURCES)
file       (APPEND ${CMAKE_SOURCE_DIR}/Makefile "popcorn-sync-objs :=\\\n")
foreach    (src   ${popcorn-sync-src})
    string (FIND ${src} ".h" src-type REVERSE)
    if   (NOT src-type EQUAL -1)
        continue()
    endif()
    string(PREPEND src "${popcorn-dir}/linux/src/sync/")
    string(REPLACE ".c" ".o" src ${src})
    file  (APPEND  ${CMAKE_SOURCE_DIR}/Makefile "\t${src}\\\n")
endforeach ()