add_kernel_module_target  (popcorn-example-start hello_world.c)
target_include_directories(popcorn-example-start PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(popcorn-example-start PRIVATE ${CMAKE_SOURCE_DIR}/linux/include)

add_kernel_module         (example-hello_world ${CMAKE_HOST_SYSTEM_VERSION})
kernel_module_link_target (example-hello_world popcorn popcorn-dev popcorn-sync popcorn-linux popcorn-example-start)
kernel_module_include     (example-hello_world ${CMAKE_SOURCE_DIR}/include)
kernel_module_include     (example-hello_world ${CMAKE_SOURCE_DIR}/linux/include)

add_kernel_module_target  (popcorn-example-chr chr.c)
target_include_directories(popcorn-example-chr PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(popcorn-example-chr PRIVATE ${CMAKE_SOURCE_DIR}/linux/include)

add_kernel_module         (example-chr ${CMAKE_HOST_SYSTEM_VERSION})
kernel_module_link_target (example-chr popcorn popcorn-dev popcorn-sync popcorn-linux popcorn-example-chr)
kernel_module_include     (example-chr ${CMAKE_SOURCE_DIR}/include)
kernel_module_include     (example-chr ${CMAKE_SOURCE_DIR}/linux/include)