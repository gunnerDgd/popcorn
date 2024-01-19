#include "linux_ns.h"

po_obj_trait po_ns_trait           = {
    .on_new   = as_new  (po_ns_new)  ,
    .on_clone = as_clone(po_ns_clone),
    .on_ref   = 0                    ,
    .on_del   = as_del  (po_ns_del)  ,
    .size     = sizeof(po_ns)
};

po_obj_trait *po_ns_t = &po_ns_trait;

bool_t
    po_ns_new
        (po_ns* par_ns, u32_t par_count, va_list par)  {
            const char* name = va_arg(par, const char*);
            if (!name)          return false_t;
            if (par_count != 1) return false_t;

            if (!make_at(&par_ns->name, po_str_t) from (0)) return false_t;
            if (!(par_ns->ns = class_create(name)))         return false_t;

            po_str_push_back_cstr(&par_ns->name, name, strlen(name));
            return true_t;
}

bool_t
    po_ns_clone
        (po_ns* par, po_ns* par_clone) {
            return false_t;
}

void
    po_ns_del
        (po_ns* par)                 {
            class_destroy(par->ns)   ;
            del          (&par->name);
}

#ifdef PO_PRESET_LINUX
#include <linux/module.h>

MODULE_LICENSE("GPL");
#endif