function   (add_module_target par_make par_name par_dir par_target_dir par_src)
    if   (UNIX AND NOT APPLE)
        include                (${popcorn-dir}/build/linux/module.cmake)
        add_linux_module_target(
            ${par_make}
            ${par_name}
            ${par_dir}
            ${par_target_dir}
            ${par_src}
        )
    endif()
endfunction()