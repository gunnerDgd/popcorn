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