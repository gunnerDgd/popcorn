if   (UNIX AND NOT APPLE)
    ksrc(popcorn-thread
        ../thread.h

        linux/thd.h
        linux/thd.c

        linux/mtx.h
        linux/mtx.c

        thd.h
        mtx.h
    )
endif()