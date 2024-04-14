add_kernel          (example 6 7.1)
kernel_build        (example)
kernel_build_bzimage(example)
kernel_config       (example)

add_kernel_image  (example-image)
kernel_image_build(example-image)
add_kernel_launch (example-launch example example-image 256)

add_kernel_feature_debug(popcorn example)
kernel_feature_source   (popcorn example
    popcorn-core
    popcorn-collections
    popcorn-thread

    popcorn-linux-dev
    popcorn-linux-fs
    popcorn-linux-thread
)

kernel_feature_include  (popcorn example ${CMAKE_SOURCE_DIR}/include)
kernel_feature_include  (popcorn example ${CMAKE_SOURCE_DIR}/linux/include)
kernel_feature_define   (popcorn example
        PRESET_ARCH_X86_64
        PRESET_ARCH_BIT=64
        PRESET_LINUX
)

add_subdirectory(core)