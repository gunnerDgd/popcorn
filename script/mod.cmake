function   (kmod NAME)
    add_kernel_module       (${NAME})
    kernel_module_source    (${NAME} ${ARGN})
    kernel_module_build_host(${NAME})

    string(APPEND VER         ${CMAKE_HOST_SYSTEM_VERSION}})
    string(APPEND INC_POPCORN ${CMAKE_CURRENT_LIST_DIR}/../include)
    string(APPEND INC         /lib/modules/${VER}/build/include)

    kernel_module_include(${NAME} INC_POPCORN)
    kernel_module_include(${NAME} INC)

    if   (PRESET_ARCH_X86_64)
        kernel_module_define  (
            ${NAME}
            PRESET_ARCH_X86_64
            PRESET_ARCH_BIT=64
        )
    endif()

    if   (PRESET_LINUX)
        kernel_module_define (${NAME} PRESET_LINUX)
    endif()
endfunction()