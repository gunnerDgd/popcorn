if(UNIX AND NOT APPLE)
    add_library(popcorn-core STATIC
        type.h
        type_atom.h

        obj.h
        linux/obj.h
        linux/obj.c

        box.h
        box.c

        mem.h
        mem.c

        str.h
        str.c

        map.h
        map.c

        list.h
        list.c
    )

    target_include_directories(popcorn-core PRIVATE /usr/src/kernels/linux-headers-${CMAKE_HOST_SYSTEM_VERSION}/include)
endif()