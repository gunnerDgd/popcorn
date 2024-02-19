define_property(TARGET PROPERTY MODULE_KERNEL_VERSION BRIEF_DOCS "Target Kernel Version of the Module")
define_property(TARGET PROPERTY MODULE_PATH           BRIEF_DOCS "Target Source's Relative Path")

if    (UNIX AND NOT APPLE)
    include(${popcorn-dir}/build/linux/module.cmake)
endif ()