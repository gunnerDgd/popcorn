add_kernel_source             (chr_src chr.c)
add_kernel_feature_with_symbol(chr example)
kernel_feature_source         (chr example
    chr_src
    popcorn-core
    popcorn-core-linux
    popcorn-linux
    popcorn-linux-dev
    popcorn-linux-sync
    popcorn-linux-fs
)
kernel_feature_definition     (chr example PRESET_ARCH_X86_64)
kernel_feature_definition     (chr example PRESET_ARCH_BIT=64)
kernel_feature_definition     (chr example PRESET_LINUX)

kernel_feature_include        (chr example ${CMAKE_SOURCE_DIR}/include)
kernel_feature_include        (chr example ${CMAKE_SOURCE_DIR}/linux/include)

target_include_directories    (chr_src PRIVATE ${CMAKE_SOURCE_DIR}/linux/include)
target_include_directories    (chr_src PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_kernel_executable         (chr_app example linux/chr_app.c)
kernel_launcher_binary        (example_launcher chr_app)