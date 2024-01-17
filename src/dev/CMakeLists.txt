if(UNIX AND NOT APPLE)
    add_library(popcorn-dev STATIC
        dev.h

            dev_type.h

            linux/details/dev.h
            linux/details/dev.c

            linux/details/dev_type.h
            linux/details/dev_type.c

        ../dev.h
            linux/dev.c
            linux/dev_type.c
    )
endif()