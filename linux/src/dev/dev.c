#include "dev.h"
#include "class.h"

#include <bit.h>
#include <linux/fs.h>

po_obj_trait po_dev_trait = po_make_trait (
    po_dev_new    ,
    po_dev_clone  ,
    null_t        ,
    po_dev_del    ,
    sizeof(po_dev),
    null_t
);

po_obj_trait *po_dev_t = &po_dev_trait;

bool_t
    po_dev_new
        (po_dev* par_dev, u32_t par_count, va_list par)                                {
            po_class *class = null_t; if (par_count > 0) class = va_arg(par, po_class*);
            po_str   *name  = null_t; if (par_count > 1) name  = va_arg(par, po_str*)  ;
            u64_t     maj   = -1    ; if (par_count > 2) maj   = va_arg(par, u64_t)    ;
            u64_t     min   = -1    ; if (par_count > 3) min   = va_arg(par, u64_t)    ;
            if (!po_make_at(&par_dev->name, po_str) from (0)) return false_t;
            if (po_trait_of(class) != po_class_t)             return false_t;
            if (po_trait_of(name)  != po_str_t)               return false_t;
            if (min >= shl (1, 19)) return false_t;
            if (maj >= shl (1, 12)) return false_t;
            par_dev->dev = device_create          (
                par_dev->class->class       ,
                null_t                      ,
                par_dev->id                 ,
                par_dev                     ,
                po_str_as_raw(&par_dev->name)
            );

            if (IS_ERR(par_dev->dev)) {
                po_del(&par_dev->name);
                return false_t;
            }

            po_str_push_back(&par_dev->name, name)    ;
            par_dev->class = (po_class*) po_ref(class);
            par_dev->id    = MKDEV(maj, min);
            return true_t;
}

bool_t
    po_dev_clone
        (po_dev* par, po_dev* par_dev) {
            return false_t;
}

void
    po_dev_del
        (po_dev* par)                                 {
            device_destroy(par->class->class, par->id);
            po_del(par->class);
            po_del(&par->name);
}