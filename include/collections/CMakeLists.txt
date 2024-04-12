add_library(popcorn-collections-include STATIC
    list.h
    map.h
    node.h
    set.h
    str.h
    seq.h
)

set_target_properties(popcorn-collections-include PROPERTIES LINKER_LANGUAGE C)