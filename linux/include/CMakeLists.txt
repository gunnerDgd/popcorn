project    (popcorn-linux-include)
add_library(popcorn-linux-include STATIC
    dev/class.h
    dev/dev.h
    dev.h

    fs/chr/chr_type.h
    fs/chr/chr.h

    fs/read.h
    fs/write.h
    fs/control.h
    fs/file_type.h
    fs/file.h
    fs.h

    thread/not.h
    thread/work.h
    thread.h
)

target_include_directories(popcorn-linux-include PRIVATE ../../include)
set_target_properties     (popcorn-linux-include PROPERTIES LINKER_LANGUAGE C)