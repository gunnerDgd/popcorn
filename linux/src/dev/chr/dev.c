#include "dev.h"
#include "chr.h"

#include <atom.h>
#include <print.h>

#include "../class.h"
#include "../dev.h"

po_obj_trait po_chr_dev_trait = po_make_trait (
    po_chr_dev_new    ,
    po_chr_dev_clone  ,
    null_t            ,
    po_chr_dev_del    ,
    sizeof(po_chr_dev),
    null_t
);

po_obj_trait *po_chr_dev_t = &po_chr_dev_trait;

bool_t
    po_chr_dev_new
        (po_chr_dev* par_dev, u32_t par_count, va_list par)                                    {
            po_str       *name  = null_t; if (par_count > 0) name  = va_arg(par, po_str*)      ;
            po_class     *class = null_t; if (par_count > 1) class = va_arg(par, po_class*)    ;
            po_chr       *chr   = null_t; if (par_count > 2) chr   = va_arg(par, po_chr*)      ;
            po_obj_trait *trait = null_t; if (par_count > 3) trait = va_arg(par, po_obj_trait*);
            if (po_trait_of(class) != po_class_t)            return false_t;
            if (po_trait_of(name)  != po_str_t)              return false_t;
            if (po_trait_of(chr)   != po_chr_t)              return false_t;
            if (!po_make_at(&par_dev->name, po_str) from(0)) return false_t;
            if (!trait)                                                    {
                po_del(&par_dev->name);
                return false_t;
            }

            par_dev->dev = (po_dev*) po_set_acq(&chr->dev);
            if(!par_dev->dev)                                                                       {
                par_dev->id  = po_lock_inc64(&chr->num); if (par_dev->id >= shl(1, 19)) goto new_err;
                par_dev->dev = po_make (po_dev) from   (
                    4         ,
                    class     ,
                    name      ,
                    chr->maj  ,
                    par_dev->id
                );

                if (po_trait_of(par_dev->dev) != po_dev_t)                     {
                    po_err("[popcorn-dev][po_chr_dev] Failed to Create Device");
                    po_del(&par_dev->name);
                    return false_t;
                }

                po_info("[popcorn-dev][po_chr_dev] No Free Device Remaining in Pool.");
                po_info("[popcorn-dev][po_chr_dev] Successfully Created Device.")     ;
            }

            cdev_init(&par_dev->chr, &chr->ops);
            if (cdev_add(&par_dev->chr, par_dev->id, 1) < 0) goto new_err;
            if (!po_dev_use(par_dev->dev))                   goto new_err;

            po_info         ("[popcorn-dev][po_chr_dev] Device Enabled");
            po_str_push_back(&par_dev->name, name);
            par_dev->trait = trait                ;
            par_dev->type  = (po_chr*) po_ref(chr);
            return true_t;
    new_err:
            po_set_rel(&chr->dev, (po_obj*) par_dev->dev);
            po_del    (&par_dev->name)                   ;
            return false_t;
}

bool_t
    po_chr_dev_clone
        (po_chr_dev* par, po_chr_dev* par_clone) {
            return false_t;
}

void
    po_chr_dev_del
        (po_chr_dev* par)                                   {
            po_dev_free(par->dev)                           ;
            cdev_del   (&par->chr)                          ;
            po_set_rel (&par->type->dev, (po_obj*) par->dev);
            po_del     (&par->name);
            po_del     (par->type) ;
}