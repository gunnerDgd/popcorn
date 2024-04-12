add_kernel          (example-kernel 6 7.1)
kernel_build_bzimage(example-kernel)
kernel_config       (example-kernel)
add_subdirectory    (hello_world)

enable_busybox    (1.36.1)
add_kernel_image  (example-image)
kernel_image_build(example-image)
add_kernel_launch (example-launch example-kernel example-image 256)