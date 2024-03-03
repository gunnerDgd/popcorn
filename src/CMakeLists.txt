cmake_minimum_required(VERSION 3.12)
add_kernel_source     (popcorn-core
        type.h
        bit.h
        atom.h
        sched.h
        task.h
        thd.h
        print.h

        fut.h
        fut.c

        mem.h
        mem.c

        node.h
        node.c

        str.h
        str.c

        list.h
        list.c

        obj.h
        obj.c

        box.h
        box.c

        map.h
        map.c

        set.h
        set.c

        ran.h
        ran.c

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

target_include_directories(popcorn-core PRIVATE ${PRESET_KERNEL_HEADER})

if    (UNIX AND NOT APPLE)
    add_kernel_source(popcorn-core-linux
        linux/atom.c
        linux/bit.c
        linux/mem.c
        linux/print.c

        linux/sched.h
        linux/sched.c

        linux/task.h
        linux/task.c

        linux/thd.h
        linux/thd.c

        linux/mod.c
    )

    target_include_directories(popcorn-core-linux PRIVATE ${PRESET_KERNEL_HEADER})
endif ()