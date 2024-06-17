if (PRESET_LINUX)
    add_kernel_source (
        popcorn-core
        ../po.h
        ../po.c

        linux/atom.c
        linux/bit.c
        linux/print.c
        linux/mod.c

        linux/heap_atomic.c
        linux/heap.c
        linux/mem.c

        type.h
        bit.h
        atom.h
        print.h

        fut.h
        fut.c

        mem.h
        mem.c

        obj.h
        obj.c

        box.h
        box.c

        task.h
        task.c

        endian.h
        endian.c

        ops.h
        ops/arith.h
        ops/arith.c

        ops/cast.h
        ops/cast.c

        ops/bit.h
        ops/bit.c

        ops/cmp.h
        ops/cmp.c

        ops/logical.h
        ops/logical.c

        sync/spsc.h
        sync/spsc.c

        sync/spmc.h
        sync/spmc.c

        sync/mpsc.h
        sync/mpsc.c

        sync/mpmc.h
        sync/mpmc.c
    )
endif()