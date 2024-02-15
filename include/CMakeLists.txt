add_library(popcorn-include STATIC
    atom.h
    bit.h
    endian.h
    fut.h
    list.h
    map.h
    mem.h
    node.h
    obj.h
    ops.h
    set.h
    str.h
    sched.h
    thd.h
    task.h
    type.h

    ops/arith.h
    ops/bit.h
    ops/cast.h
    ops/cmp.h
    ops/logical.h

    sync/mpmc.h
    sync/mpsc.h
    sync/spmc.h
    sync/spsc.h
)

set_target_properties(popcorn-include PROPERTIES LINKER_LANGUAGE C)