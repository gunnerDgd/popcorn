add_library(popcorn-collections-include STATIC
    ../collections.h
    list.h
    map.h
    node.h
    bma.h
    str.h
    seq.h
)

set_target_properties(popcorn-collections-include PROPERTIES LINKER_LANGUAGE C)