add_kernel_module_target  (popcorn-example-start start/mod.c)
target_include_directories(popcorn-example-start PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(popcorn-example-start PRIVATE ${CMAKE_SOURCE_DIR}/linux/include)
add_kernel_module         (start ${CMAKE_HOST_SYSTEM_VERSION})

kernel_module_link_target(start popcorn popcorn-dev popcorn-sync popcorn-linux popcorn-example-start)
kernel_module_include    (start ${CMAKE_SOURCE_DIR}/include)
kernel_module_include    (start ${CMAKE_SOURCE_DIR}/linux/include)