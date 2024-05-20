add_kernel_source(popcorn-collections
    ../collections.h

    list.h
    list.c

    map.h
    map.c

    node.h
    node.c

    seq.h
    seq.c

    set.h
    set.c

    str.h
    str.c
)

target_include_directories(popcorn-collections PRIVATE /lib/modules/${CMAKE_HOST_SYSTEM_VERSION}/build/include)