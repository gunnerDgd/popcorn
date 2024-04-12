if  (PO_FEATURE_LINUX)
    add_subdirectory     (dev)
    add_subdirectory     (thread)
    add_subdirectory     (fs)
    kernel_module_source (popcorn
        popcorn-linux-thread
        popcorn-linux-dev
        popcorn-linux-fs
    )
endif()