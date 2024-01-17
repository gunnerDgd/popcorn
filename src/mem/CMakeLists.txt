if(UNIX AND NOT APPLE)
    add_library(popcorn-mem STATIC
        buf.h
            linux/buf.c

            linux/details/buf.h
            linux/details/buf.c

        ../mem.h
    )
endif()