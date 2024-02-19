function   (add_linux_make par_make par_module_name)
    file (REMOVE ${CMAKE_SOURCE_DIR}/${par_make})
    file (APPEND ${CMAKE_SOURCE_DIR}/${par_make} "obj-m += ${par_module_name}.o\n")
endfunction()

function   (add_linux_make_target par_make par_module_name par_target_dir)
    file (APPEND ${CMAKE_SOURCE_DIR}/${par_make} "${par_module_name}-y += \\\n")
    foreach    (src IN LISTS ARGN)
        string (FIND ${src} ".h" src_type REVERSE)
        if   (NOT src_type EQUAL -1)
            continue()
        endif()

        string(PREPEND src "${par_target_dir}/")
        string(REPLACE ".c" ".o" src ${src})
        file  (APPEND  ${CMAKE_SOURCE_DIR}/${par_make} "\t${src}\\\n")
    endforeach ()
    file  (APPEND  ${CMAKE_SOURCE_DIR}/${par_make} "\n")
endfunction()

function   (add_linux_make_command par_make par_target)
    set    (par_define)
    if     (PRESET_ARCH_X86_64)
        string(APPEND par_define "-DPRESET_LINUX ")
        string(APPEND par_define "-DPRESET_ARCH_X86_64 ")
        string(APPEND par_define "-DPRESET_ARCH_BIT=64 ")
        string(APPEND par_define "-DPRESET_ARCH_ENDIAN_LITTLE ")
        string(APPEND par_define "-I${popcorn-dir}/include ")
        string(APPEND par_define "-I${popcorn-dir}/linux/include ")
    elseif (PRESET_ARCH_X86)
        string(APPEND par_define "-DPRESET_LINUX ")
        string(APPEND par_define "-DPRESET_ARCH_X86 ")
        string(APPEND par_define "-DPRESET_ARCH_BIT=32 ")
        string(APPEND par_define "-DPRESET_ARCH_ENDIAN_LITTLE")
    endif  ()
    file   (REMOVE ${CMAKE_SOURCE_DIR}/Kbuild)
    add_custom_command                                     (
            OUTPUT            ${par_target}.ko
            COMMAND           cp ${CMAKE_SOURCE_DIR}/${par_make} ${CMAKE_SOURCE_DIR}/Kbuild
            COMMAND           make KCPPFLAGS=${par_define} -C /lib/modules/${CMAKE_HOST_SYSTEM_VERSION}/build M=${CMAKE_SOURCE_DIR} modules
            COMMAND           rm ${CMAKE_SOURCE_DIR}/Kbuild
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            DEPENDS           ${CMAKE_SOURCE_DIR}/${par_make}
            VERBATIM)
    add_custom_target(${par_target}-module       DEPENDS ${par_target}.ko)
    add_custom_target(${par_target}-module-clean
        COMMAND cp ${CMAKE_SOURCE_DIR}/${par_make} ${CMAKE_SOURCE_DIR}/Kbuild
        COMMAND make -C /lib/modules/${CMAKE_HOST_SYSTEM_VERSION}/build M=${CMAKE_SOURCE_DIR} clean
        COMMAND rm ${CMAKE_SOURCE_DIR}/Kbuild
    )
endfunction()