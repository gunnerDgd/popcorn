function   (arch_define)
    if     (PRESET_ARCH_X86_64)
        add_compile_definitions(PRESET_ARCH_X86_64)
        add_compile_definitions(PRESET_ARCH_BIT=64)
        add_compile_definitions(PRESET_ARCH_ENDIAN_LITTLE)
    elseif (PRESET_ARCH_X86)
        add_compile_definitions(PRESET_ARCH_X86)
        add_compile_definitions(PRESET_ARCH_BIT=32)
        add_compile_definitions(PRESET_ARCH_ENDIAN_LITTLE)
    endif()
endfunction()

function   (compiler_define)
    if     ("${CMAKE_C_COMPILER_ID}" MATCHES  "Clang")
        add_compile_definitions(PRESET_COMPILER_CLANG)
        add_compile_definitions(PRESET_CALL_SYSV)
    elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
        add_compile_definitions(PRESET_COMPILER_GCC)
        add_compile_definitions(PRESET_CALL_SYSV)
    elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "Intel")
        add_compile_definitions(PRESET_COMPILER_INTEL)
        add_compile_definitions(PRESET_CALL_SYSV)
    elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
        add_compile_definitions(PRESET_COMPILER_MSVC)
        add_compile_definitions(PRESET_CALL_VECTORCALL)
    endif()
endfunction()

function   (environment_define)
    if    (WIN32)
        add_compile_definitions(PRESET_WIN32)
    elseif(UNIX AND NOT APPLE)
        add_compile_definitions(PRESET_LINUX)
        include_directories    (/usr/src/linux-headers-${CMAKE_HOST_SYSTEM_VERSION}/include)
        include_directories    (/usr/src/kernels/${CMAKE_HOST_SYSTEM_VERSION}/include)
    endif ()
endfunction()