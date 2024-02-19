add_library               (popcorn-example-start STATIC start/mod.c)
target_include_directories(popcorn-example-start PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(popcorn-example-start PRIVATE ${CMAKE_SOURCE_DIR}/linux/include)
add_module_target         (start start . ./example/start "mod.c")