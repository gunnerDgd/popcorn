add_kernel_source             (hello_world_src hello_world.c)
add_kernel_feature_with_symbol(hello_world     example)
kernel_feature_source         (hello_world     example hello_world_src popcorn-core popcorn-core-linux popcorn-linux)
kernel_feature_definition     (hello_world     example PRESET_ARCH_X86_64)
kernel_feature_definition     (hello_world     example PRESET_ARCH_BIT=64)
kernel_feature_definition     (hello_world     example PRESET_LINUX)

target_include_directories(hello_world_src PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(hello_world_src PRIVATE ${CMAKE_SOURCE_DIR}/linux/include)

target_include_directories(hello_world_src PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(hello_world_src PRIVATE ${CMAKE_SOURCE_DIR}/linux/include)

kernel_feature_include    (hello_world example ${CMAKE_SOURCE_DIR}/include)
kernel_feature_include    (hello_world example ${CMAKE_SOURCE_DIR}/linux/include)