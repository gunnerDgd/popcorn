#include "dev.h"
#include "class.h"

#include <linux/fs.h>

po_obj*
    po_dev_do_cast
        (po_dev* par, po_obj_trait* par_trait)                                {
            if (po_trait_of(par) != po_dev_t)                    return null_t;
            if (po_trait_of(par->dev->driver_data) != par_trait) return null_t;
            return par->dev->driver_data;
}

po_ops_cast po_dev_ops_cast = po_make_cast_ops (
    po_dev_do_cast,
    null_t        ,
    null_t        ,
    null_t        ,
    null_t        ,
    null_t        ,
    null_t        ,
    null_t        ,
    null_t
);

po_obj_ops po_dev_ops     = {
    .cast = &po_dev_ops_cast
};

po_obj_trait po_dev_trait = po_make_trait (
    po_dev_new    ,
    po_dev_clone  ,
    null_t        ,
    po_dev_del    ,
    sizeof(po_dev),
    &po_dev_ops
);

po_obj_trait *po_dev_t = &po_dev_trait;

bool_t
    po_dev_new
        (po_dev* par_dev, u32_t par_count, va_list par) {
            par_dev->dev = null_t;
            return true_t;
}

bool_t po_dev_clone(po_dev* par, po_dev* par_dev) { return false_t; }
void   po_dev_del  (po_dev* par)                  { put_device(par->dev); }

#include <linux/module.h>

MODULE_LICENSE("GPL");
EXPORT_SYMBOL(po_dev_t);