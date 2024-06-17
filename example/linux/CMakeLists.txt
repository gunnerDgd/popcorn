add_kernel          (example 6 8.11)
kernel_build        (example 4)
kernel_build_bzimage(example 4)
kernel_config       (example)

add_kernel_image    (example-image)
kernel_image_build  (example-image)
add_kernel_launch   (example-launch example example-image 256)

add_kernel_feature(popcorn example)

add_kernel_source (hello hello.c)
add_kernel_feature(hello example)

add_kernel_source (thread thread.c)
add_kernel_feature(thread example thread)

kernel_feature_include(hello  example ${ROOT_LIB}/popcorn/include)
kernel_feature_include(thread example ${ROOT_LIB}/popcorn/include)

kernel_feature_source (hello   example hello)
kernel_feature_source (thread  example thread)
kernel_feature_source (popcorn example
    popcorn-core
    popcorn-collections
    popcorn-thread
)