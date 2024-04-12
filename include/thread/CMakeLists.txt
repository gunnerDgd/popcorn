add_library(popcorn-include-thread STATIC
    mtx.h
    thd.h
)

set_target_properties(popcorn-include-thread PROPERTIES LINKER_LANGUAGE C)