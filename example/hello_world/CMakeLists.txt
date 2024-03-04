add_kernel                    (example-hello_world-kernel 6 7.1)
add_kernel_launcher           (example-hello_world-kernel-launcher example-hello_world-kernel)
add_kernel_source             (example-hello_world_src hello_world.c)
add_kernel_feature_with_symbol(example-hello_world     example-hello_world-kernel)
kernel_feature_source         (example-hello_world     example-hello_world-kernel
    example-hello_world_src
    popcorn-core
    popcorn-core-linux
    popcorn-linux-com
)

kernel_feature_definition     (example-hello_world     example-hello_world-kernel PRESET_ARCH_X86_64)
kernel_feature_definition     (example-hello_world     example-hello_world-kernel PRESET_ARCH_BIT=64)
kernel_feature_definition     (example-hello_world     example-hello_world-kernel PRESET_LINUX)

target_include_directories    (example-hello_world_src PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories    (example-hello_world_src PRIVATE ${CMAKE_SOURCE_DIR}/linux/include)

target_include_directories    (example-hello_world_src PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories    (example-hello_world_src PRIVATE ${CMAKE_SOURCE_DIR}/linux/include)

kernel_feature_include        (example-hello_world example-hello_world-kernel ${CMAKE_SOURCE_DIR}/include)
kernel_feature_include        (example-hello_world example-hello_world-kernel ${CMAKE_SOURCE_DIR}/linux/include)