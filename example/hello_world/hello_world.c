#include "obj.h"
#include "print.h"
#include "com.h"

bool_t
    ModInit(po_obj* par_mod, u32_t par_count, va_list par) {
        po_info("Hello World !!");
        cstr_t  name_cstr = cstr("dev")             ;
        po_str *name      = po_make(po_str) from (0);
        po_str_push_back_cstr(name, name_cstr);
        po_com *com     = po_com_root    ()              ;
        po_com *com_dev = po_com_sub_cstr(com, name_cstr);

        po_del(com_dev);
        po_del(com)    ;
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