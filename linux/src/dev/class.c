#include "class.h"

po_obj_trait po_class_trait = po_make_trait (
    po_class_new    ,
    po_class_clone  ,
    null_t          ,
    po_class_del    ,
    sizeof(po_class),
    null_t
);

po_obj_trait *po_class_t = &po_class_trait;

bool_t
    po_class_new
        (po_class* par_cls, u32_t par_count, va_list par)                        {
            po_str* name = null_t; if (par_count > 0) name = va_arg(par, po_str*);
            if (po_trait_of(name) != po_str_t)                return false_t;
            if (!po_make_at(&par_cls->name, po_str) from (0)) return false_t;
            par_cls->class = class_create(po_str_as_raw(name));
            if (IS_ERR (par_cls->class))                      {
                po_del(&par_cls->name);
                return false_t;
            }

            po_str_push_back(&par_cls->name, name);
            return true_t;
}

bool_t
    po_class_clone
        (po_class* par, po_class* par_clone) {
            return false_t;
}

void
    po_class_del
        (po_class* par)              {
            class_destroy(par->class);
            po_del       (&par->name);
}

#ifdef PO_PRESET_LINUX
#include <linux/module.h>

MODULE_LICENSE("GPL");
#endif