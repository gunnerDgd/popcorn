add_kernel          (example 6 8.11)
kernel_build        (example 4)
kernel_build_bzimage(example 4)
kernel_config       (example)

add_kernel_image    (example-image)
kernel_image_build  (example-image)
add_kernel_launch   (example-launch example example-image 256)

kernel_feature      (
    popcorn
    example
    popcorn-core
    popcorn-collections
    popcorn-thread
)

kernel_source (hello hello.c)
kernel_feature(hello example hello)

kernel_source (thread thread.c)
kernel_feature(thread example thread)