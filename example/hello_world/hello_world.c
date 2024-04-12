#include <obj.h>
#include <print.h>

#include <com/com.h>
#include <com/class.h>

bool_t
    ModInit(po_obj* par_mod, u32_t par_count, va_list par) {
        po_info("Hello World !!");
        return true_t;
}

void
    ModDeinit(po_obj* par_mod)     {
        po_info("Goodbye World !!");
}

po_obj_trait mod_trait = po_make_trait (
    ModInit  ,
    null_t   ,
    null_t   ,
    ModDeinit,
    64       ,
    null_t
);

po_obj_trait* mod_t = &mod_trait;

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");
#endif