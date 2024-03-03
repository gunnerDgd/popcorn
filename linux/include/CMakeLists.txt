project    (popcorn-linux-include)
add_library(popcorn-linux-include STATIC
    com/com.h
    com/dev.h
    com/class.h
    com/bus.h

    dev/class.h
    dev/dev.h

    fs/chr/chr_type.h
    fs/chr/chr.h

    fs/read.h
    fs/write.h
    fs/control.h
    fs/file_type.h
    fs/file.h

    sync/not.h
    sync/work.h
    sync/mtx.h
)

set_target_properties     (popcorn-linux-include PROPERTIES LINKER_LANGUAGE C)
target_include_directories(popcorn-linux-include PRIVATE ../../include)