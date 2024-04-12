add_kernel_feature_debug(example_core_basic example)
add_kernel_source       (example_core_basic basic.c)

kernel_feature_source   (example_core_basic example example_core_basic)
kernel_feature_include  (example_core_basic example ${CMAKE_SOURCE_DIR}/include)
kernel_feature_include  (example_core_basic example ${CMAKE_SOURCE_DIR}/linux/include)
kernel_feature_define   (example_core_basic example
    PRESET_ARCH_X86_64
    PRESET_ARCH_BIT=64
    PRESET_LINUX
)

target_compile_definitions (example_core_basic PRIVATE
    PRESET_ARCH_X86_64
    PRESET_ARCH_BIT=64
    PRESET_LINUX
)

target_include_directories (example_core_basic PRIVATE
    /usr/src/kernels/${CMAKE_HOST_SYSTEM_VERSION}/include
    /usr/src/${CMAKE_HOST_SYSTEM_VERSION}/include
    ../../../include
    ../../../linux/include
)