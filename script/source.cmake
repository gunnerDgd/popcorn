function   (kernel_source NAME)
    add_kernel_source(${NAME} ${ARGN})
    string(APPEND VER         ${CMAKE_HOST_SYSTEM_VERSION})
    string(APPEND INC_POPCORN ${POPCORN_ROOT}/include)
    string(APPEND INC         /lib/modules/${VER}/build/include)

    target_include_directories(${NAME} PRIVATE ${INC_POPCORN})
    target_include_directories(${NAME} PRIVATE ${INC})
endfunction()