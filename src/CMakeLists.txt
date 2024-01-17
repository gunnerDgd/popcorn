add_subdirectory(core)
add_subdirectory(dev)
add_subdirectory(mem)

add_library  (popcorn STATIC
        po_linux.h
        po_linux.c
)