add_kernel_module_target(popcorn-dev
    dev.h
    dev.c

    class.h
    class.c

    chr/read.h
    chr/read.c

    chr/write.h
    chr/write.c

    chr/con.h
    chr/con.c

    chr/chr.h
    chr/chr.c

    chr/dev.h
    chr/dev.c
)

target_include_directories(popcorn-dev PRIVATE /usr/src/kernels/${CMAKE_HOST_SYSTEM_VERSION}/include)
target_include_directories(popcorn-dev PRIVATE /usr/src/linux-headers-${CMAKE_HOST_SYSTEM_VERSION}/include)
target_include_directories(popcorn-dev PRIVATE ../../../include)