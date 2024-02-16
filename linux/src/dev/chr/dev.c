#include "dev.h"
#include "type.h"

#include "../class.h"
#include "../dev.h"

bool_t
    po_chr_dev_new
        (po_chr_dev* par_dev, u32_t par_count, va_list par)                                    {
            po_str       *name  = null_t; if (par_count > 0) name  = va_arg(par, po_str*)      ;
            po_class     *class = null_t; if (par_count > 1) class = va_arg(par, po_class*)    ;
            po_chr_type  *type  = null_t; if (par_count > 2) type  = va_arg(par, po_chr_type*) ;
            po_obj_trait *trait = null_t; if (par_count > 3) trait = va_arg(par, po_obj_trait*);
            if (!trait)                                      return false_t;
            if (po_trait_of(class) != po_class_t)            return false_t;
            if (po_trait_of(type)  != po_chr_type_t)         return false_t;
            if (po_trait_of(name)  != po_str_t)              return false_t;
            if (!po_make_at(&par_dev->name, po_str) from(0)) return false_t;
            par_dev->id = MKDEV(type->maj, po_lock_inc64(&type->min));

            cdev_init(&par_dev->chr, &type->type);
            if (cdev_add(&par_dev->chr, par_dev->id, 1) < 0) return false_t;
            if (!(par_dev->dev = (po_dev*) po_set_acq(&type->dev)))        {
                if (type->min == type->num) return false_t;
                par_dev->dev = po_make (po_dev) from      (
                    4        ,
                    class    ,
                    name     ,
                    type->maj,
                    type->min
                );
            }

            if (!par_dev->dev)            return false_t;
            if (po_dev_use(par_dev->dev)) return false_t;
            po_str_push_back(&par_dev->name, name);
            par_dev->type  = po_ref(type);
            par_dev->trait = trait       ;
            return true_t;
}

bool_t
    po_chr_dev_clone
        (po_chr_dev* par, po_chr_dev* par_clone) {
            return false_t;
}

void
    po_chr_dev_del
        (po_chr_dev* par)                                   {
            po_set_rel (&par->type->dev, (po_obj*) par->dev);
            cdev_del   (&par->chr);
            po_dev_free(par->dev) ;
            po_del  (&par->name);
            po_del  (par->type) ;
}