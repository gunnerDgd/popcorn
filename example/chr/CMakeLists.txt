add_kernel                    (example-chr-kernel 6 7.1)
add_kernel_launcher           (example-chr-kernel-launcher example-chr-kernel)
add_kernel_source             (example-chr_src chr.c)
add_kernel_feature_with_symbol(example-chr example-chr-kernel)
kernel_feature_source         (example-chr example-chr-kernel
    example-chr_src
    popcorn-core
    popcorn-core-linux
    popcorn-linux-dev
    popcorn-linux-sync
    popcorn-linux-fs
)


kernel_feature_definition     (example-chr example-chr-kernel PRESET_ARCH_X86_64)
kernel_feature_definition     (example-chr example-chr-kernel PRESET_ARCH_BIT=64)
kernel_feature_definition     (example-chr example-chr-kernel PRESET_LINUX)

kernel_feature_include        (example-chr example-chr-kernel ${CMAKE_SOURCE_DIR}/include)
kernel_feature_include        (example-chr example-chr-kernel ${CMAKE_SOURCE_DIR}/linux/include)

target_include_directories    (example-chr_src PRIVATE ${CMAKE_SOURCE_DIR}/linux/include)
target_include_directories    (example-chr_src PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_kernel_executable         (example-chr_app             example-chr-kernel linux/chr_app.c)
kernel_launcher_binary        (example-chr-kernel-launcher example-chr_app)

add_host_kernel_module        (example-chr)
host_kernel_module_source     (example-chr
    example-chr_src
    popcorn-core
    popcorn-core-linux
    popcorn-linux-dev
    popcorn-linux-sync
    popcorn-linux-fs
)

host_kernel_module_definition     (example-chr PRESET_ARCH_X86_64)
host_kernel_module_definition     (example-chr PRESET_ARCH_BIT=64)
host_kernel_module_definition     (example-chr PRESET_LINUX)

host_kernel_module_include        (example-chr ${CMAKE_SOURCE_DIR}/include)
host_kernel_module_include        (example-chr ${CMAKE_SOURCE_DIR}/linux/include)