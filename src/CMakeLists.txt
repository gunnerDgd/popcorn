cmake_minimum_required(VERSION 3.12)
add_library           (popcorn STATIC
        type.h
        bit.h
        atom.h
        sched.h
        task.h
        thd.h

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

if    (PRESET_LINUX)
    add_library(popcorn-linux STATIC
            linux/atom.c
            linux/bit.c
            linux/mem.c

            linux/sched.h
            linux/sched.c

            linux/task.h
            linux/task.c

            linux/thd.h
            linux/thd.c
    )

    target_link_libraries(popcorn PRIVATE popcorn-linux)
    file (APPEND ${CMAKE_SOURCE_DIR}/Makefile "popcorn-objs :=\\\n")
    set  (popcorn-src-linux)
    set  (popcorn-src-all)
    set  (popcorn-src)

    get_target_property(popcorn-src-linux popcorn-linux SOURCES)
    get_target_property(popcorn-src       popcorn       SOURCES)
    list(APPEND popcorn-src-all ${popcorn-src-linux})
    list(APPEND popcorn-src-all ${popcorn-src})

    foreach    (src ${popcorn-src-all})
        string (FIND ${src} ".h" src-type REVERSE)
        if   (NOT src-type EQUAL -1)
            continue()
        endif()
        string(PREPEND src "${popcorn-dir}/src/core/")
        string(REPLACE ".c" ".o" src ${src})
        file  (APPEND  ${CMAKE_SOURCE_DIR}/Makefile "\t${src}\\\n")
    endforeach ()
    file  (APPEND  ${CMAKE_SOURCE_DIR}/Makefile "\n")
endif ()