if   (UNIX AND NOT APPLE)
    add_kernel_source(popcorn-thread
        ../thread.h

        linux/thd.h
        linux/thd.c

        linux/mtx.h
        linux/mtx.c

        thd.h
        mtx.h
    )

    target_include_directories(popcorn-thread PRIVATE /lib/modules/${CMAKE_HOST_SYSTEM_VERSION}/build/include)
endif()