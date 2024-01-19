if(UNIX AND NOT APPLE)
    add_library(popcorn-mem STATIC
        buf.h

            details/linux_buf.h
            details/linux_buf.c

        ../mem.h
    )
    target_include_directories(popcorn-mem PRIVATE /usr/src/kernels/linux-headers-${CMAKE_HOST_SYSTEM_VERSION}/include)
endif()