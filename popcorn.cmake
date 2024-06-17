set(POPCORN_ROOT ${CMAKE_CURRENT_LIST_DIR} PARENT_SCOPE)
set(POPCORN_ROOT ${CMAKE_CURRENT_LIST_DIR})

include (${CMAKE_CURRENT_LIST_DIR}/script/feature.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/script/module.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/script/source.cmake)

include_directories(/lib/modules/${CMAKE_HOST_SYSTEM_VERSION}/build/include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)