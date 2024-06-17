if   (PRESET_LINUX)
    add_kernel_source (
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