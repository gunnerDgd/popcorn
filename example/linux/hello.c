#include <core.h>
#include <collections.h>
#include <thread.h>

#include <linux/module.h>

static int
    mod_init (void)                {
        po_info("Hello Popcorn !!");
        return 0;
}

static void
    mod_exit (void)                   {
        po_info ("Goodbye Popcorn !!");
}

module_init(mod_init)
module_exit(mod_exit)

MODULE_LICENSE("GPL");