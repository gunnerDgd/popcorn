if(UNIX AND NOT APPLE)
    add_library(popcorn-dev STATIC
        dev.h

            chr.h

            details/linux_dev.h
            details/linux_dev.c

            details/linux_chr.h
            details/linux_chr.c

            details/linux_ns.h
            details/linux_ns.c

            ../dev.h
            chr.c
            ns.h
            dev.c
            ns.c
    )

    target_include_directories(popcorn-dev PRIVATE /usr/src/kernels/linux-headers-${CMAKE_HOST_SYSTEM_VERSION}/include)
endif()