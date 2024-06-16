add_subdirectory(core)

if   (PO_FEATURE_COLLECTIONS)
    add_subdirectory(collections)
endif()

if   (PO_FEATURE_THREAD)
    add_subdirectory(thread)
endif()