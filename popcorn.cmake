set(POPCORN_ROOT ${CMAKE_CURRENT_LIST_DIR})

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
if   (PRESET_LINUX)
    include_directories(/lib/modules/${CMAKE_HOST_SYSTEM_VERSION}/build/include)
endif()