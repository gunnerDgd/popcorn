add_library(popcorn-core-include
    ../core.h

    atom.h
    bit.h
    endian.h
    fut.h
    obj.h
    print.h
    type.h
    task.h
    box.h
    mem.h
    mod.h

    sync/spsc.h
    sync/spmc.h
    sync/mpsc.h
    sync/mpmc.h

    ops.h
    ops/arith.h
    ops/bit.h
    ops/cast.h
    ops/cmp.h
    ops/logical.h
)

set_target_properties(popcorn-core-include PROPERTIES LINKER_LANGUAGE C)