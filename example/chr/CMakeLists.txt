add_kernel_source             (chr_src chr.c)
add_kernel_feature_with_symbol(chr example)
kernel_feature_source         (chr example chr_src popcorn popcorn-linux popcorn-dev popcorn-sync)
kernel_feature_definition     (chr example PRESET_ARCH_X86_64)
kernel_feature_definition     (chr example PRESET_ARCH_BIT=64)
kernel_feature_definition     (chr example PRESET_LINUX)

kernel_feature_include        (chr example ${CMAKE_SOURCE_DIR}/include)
kernel_feature_include        (chr example ${CMAKE_SOURCE_DIR}/linux/include)