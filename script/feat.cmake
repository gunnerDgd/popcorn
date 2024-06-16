function   (kfeat NAME KERNEL)
    add_kernel_feature      (${NAME} ${KERNEL})
    kernel_feature_source   (${NAME} ${KERNEL} ${ARGN})

    string(APPEND VER         ${CMAKE_HOST_SYSTEM_VERSION}})
    string(APPEND INC_POPCORN ${CMAKE_CURRENT_LIST_DIR}/../include)
    string(APPEND INC         /lib/modules/${VER}/build/include)

    kernel_feature_include(${NAME} ${KERNEL} ${INC_POPCORN})
    kernel_feature_include(${NAME} ${KERNEL} ${INC})

    if   (PRESET_ARCH_X86_64)
        kernel_feature_define  (
            ${NAME}
            ${KERNEL}
            PRESET_ARCH_X86_64
            PRESET_ARCH_BIT=64
        )
    endif()

    if   (PRESET_LINUX)
        kernel_feature_define (${NAME} ${KERNEL} PRESET_LINUX)
    endif()
endfunction()