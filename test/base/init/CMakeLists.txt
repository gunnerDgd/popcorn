add_kernel          (test-base-init 6 7.1)
kernel_build_bzimage(test-base-init)
kernel_clean        (test-base-init)

add_kernel_image    (test-base-init-image)
kernel_image_build  (test-base-init-image)
add_kernel_launch   (test-base-init-launch test-base-init test-base-init-image 256)

add_kernel_feature_debug(test-base-init test-base-init)
kernel_feature_source   (test-base-init test-base-init
        popcorn-core
        popcorn-collections
        popcorn-thread

)

kernel_feature_define    (test-base-init test-base-init
        PRESET_ARCH_X86_64
        PRESET_ARCH_BIT=64
        PRESET_LINUX
)

kernel_feature_include(test-base-init test-base-init ${CMAKE_SOURCE_DIR}/include)