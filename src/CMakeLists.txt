cmake_minimum_required(VERSION 3.12)
add_library           (popcorn STATIC
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

if    (UNIX AND NOT APPLE)
    add_library(popcorn-linux STATIC
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

    file(RELATIVE_PATH popcorn-path ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
    set_target_properties(popcorn-linux PROPERTIES MODULE_PATH ${popcorn-path})
    set_target_properties(popcorn       PROPERTIES MODULE_PATH ${popcorn-path})
endif ()