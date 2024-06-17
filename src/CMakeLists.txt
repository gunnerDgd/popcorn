add_subdirectory(core)

if   (POPCORN_FEATURE_COLLECTIONS)
    add_subdirectory(collections)
endif()

if   (POPCORN_FEATURE_THREAD)
    add_subdirectory(thread)
endif()