if   (PRESET_LINUX)
    kernel_source     (
        popcorn-thread
        ../thread.h

        linux/thd.h
        linux/thd.c

        linux/mut.h
        linux/mut.c

        thd.h
        mut.h
    )
endif()