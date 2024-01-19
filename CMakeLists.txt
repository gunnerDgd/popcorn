project         (popcorn)

if (UNIX AND NOT APPLE)
    add_compile_definitions(PO_PRESET_LINUX)
    #include_directories    (/usr/src/linux-headers-${CMAKE_HOST_SYSTEM_VERSION}/include)
    include_directories    (/usr/src/kernels/${CMAKE_HOST_SYSTEM_VERSION}/include)
    message                ("/usr/src/kernels/linux-headers-${CMAKE_HOST_SYSTEM_VERSION}/include")
endif()

add_subdirectory(src)
add_subdirectory(include/popcorn)
add_subdirectory(example)