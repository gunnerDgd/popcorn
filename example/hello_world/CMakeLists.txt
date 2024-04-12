add_kernel_source    (example-hello_world_src hello_world.c)
add_kernel_feature   (example-hello_world example-kernel)
kernel_feature_source(example-hello_world example-kernel
    example-hello_world_src
    popcorn-core
)

kernel_feature_define   (example-hello_world example-kernel
    PRESET_ARCH_X86_64
    PRESET_ARCH_BIT=64
    PRESET_LINUX
)

target_include_directories(example-hello_world_src PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(example-hello_world_src PRIVATE ${CMAKE_SOURCE_DIR}/linux/include)

target_include_directories(example-hello_world_src PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(example-hello_world_src PRIVATE ${CMAKE_SOURCE_DIR}/linux/include)

kernel_feature_include(example-hello_world example-kernel ${CMAKE_SOURCE_DIR}/include)
kernel_feature_include(example-hello_world example-kernel ${CMAKE_SOURCE_DIR}/linux/include)