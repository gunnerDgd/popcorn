add_subdirectory    (core)
kernel_module_source(popcorn popcorn-core)

if   (PO_FEATURE_COLLECTIONS)
    add_subdirectory    (collections)
    kernel_module_source(popcorn popcorn-collections)
endif()

if   (PO_FEATURE_THREAD)
    add_subdirectory    (thread)
    kernel_module_source(popcorn popcorn-thread)
endif()