add_kernel_source(popcorn-linux-fs
    chr/chr_type.h
    chr/chr_type.c

    chr/chr.h
    chr/chr.c

    chr.h
    chr.c

    control.h
    control.c

    write.h
    write.c

    read.h
    read.c

    file_type.h
    file_type.c

    file.h
    file.c
)

target_include_directories(popcorn-linux-fs PRIVATE ../../../include)
target_include_directories(popcorn-linux-fs PRIVATE ${PRESET_KERNEL_HEADER})