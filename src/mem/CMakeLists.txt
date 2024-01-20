if(UNIX AND NOT APPLE)
    add_library(popcorn-mem STATIC
            ubuf.h

            details/linux_ubuf.h
            details/linux_ubuf.c

        ../mem.h
            heap.h
            details/linux_heap.h
            details/linux_heap.c
            details/linux_page.h
            details/linux_page.c
            page.h
    )
    target_include_directories(popcorn-mem PRIVATE /usr/src/kernels/linux-headers-${CMAKE_HOST_SYSTEM_VERSION}/include)
endif()