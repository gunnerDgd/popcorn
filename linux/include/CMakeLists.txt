project    (popcorn-linux-include)
add_library(popcorn-linux-include STATIC
    dev/chr/chr.h
    dev/chr/con.h
    dev/chr/dev.h
    dev/chr/read.h
    dev/chr/write.h

    dev/class.h
    dev/dev.h

    sync/not.h
    sync/work.h
    sync/mtx.h
)

set_target_properties     (popcorn-linux-include PROPERTIES LINKER_LANGUAGE C)
target_include_directories(popcorn-linux-include PRIVATE ../../include)