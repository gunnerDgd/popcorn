set        (popcorn-dev-src)
add_library(popcorn-dev STATIC
    dev.h
    dev.c

    class.h
    class.c

    chr/read.h
    chr/read.c

    chr/write.h
    chr/write.c

    chr/con.h
    chr/con.c

    chr/chr.h
    chr/chr.c

    chr/dev.h
    chr/dev.c

)

target_include_directories(popcorn-dev PRIVATE ../../../include)
get_target_property       (popcorn-dev-src popcorn-dev SOURCES)
file       (APPEND ${CMAKE_SOURCE_DIR}/Makefile "popcorn-dev-objs :=\\\n")
foreach    (src   ${popcorn-dev-src})
    string (FIND ${src} ".h" src-type REVERSE)
    if   (NOT src-type EQUAL -1)
        continue()
    endif()
    string(PREPEND src "${popcorn-dir}/linux/src/dev/")
    string(REPLACE ".c" ".o" src ${src})
    file  (APPEND  ${CMAKE_SOURCE_DIR}/Makefile "\t${src}\\\n")
endforeach ()