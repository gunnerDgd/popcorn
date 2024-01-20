add_library(popcorn-include STATIC
    core.h
    core/list.h
    core/map.h
    core/mem.h
    core/obj.h
    core/str.h
    core/type.h
    core/type_atom.h

    dev.h
    dev/dev.h
    dev/chr.h
    dev/ns.h

    mem.h
        mem/ubuf.h
        dev/chr_dev.h
        mem/heap.h
        mem/page.h
)

set_target_properties(popcorn-include PROPERTIES LINKER_LANGUAGE C)