#include <core.h>
#include <dev.h>
#include <linux/module.h>

static int
    mod_init (void)                {
        po_info("Hello Popcorn !!");
        po_str *name = po_make (po_str) from (0);
        po_str_push_back_cstr(name, "Hello", 6);
        po_class *class = po_make (po_class) from (1, name);
        return 0;
}

static void
    mod_exit (void)                   {
        po_info ("Goodbye Popcorn !!");
}

module_init(mod_init)
module_exit(mod_exit)

MODULE_LICENSE("GPL");