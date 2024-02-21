#include "dev.h"
#include "chr.h"
#include "../class.h"

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
            po_chr_ops   *ops   = null_t; if (par_count > 4) ops   = va_arg(par, po_chr_ops*)  ;
            dev_t         min   = -1    ; if (par_count > 5) min   = va_arg(par, dev_t)        ;
            if (po_trait_of(class) != po_class_t) return false_t;
            if (po_trait_of(name)  != po_str_t)   return false_t;
            if (po_trait_of(chr)   != po_chr_t)   return false_t;
            if (min >= chr->min) return false_t;
            if (min == -1)       return false_t;
            if (!trait)          return false_t;
            if (!ops)            return false_t;

            cdev_init   (&par_dev->chr, &chr->ops);
            if (cdev_add(&par_dev->chr, chr->maj + min, 1) < 0)                                 return false_t;
            if (!po_make_at(&par_dev->dev, po_dev) from (4, class, name, MAJOR(chr->maj), min)) return false_t;
            par_dev->type  = (po_chr*) po_ref(chr);
            par_dev->trait = trait;
            par_dev->ops   = ops  ;
            return true_t;
}

bool_t
    po_chr_dev_clone
        (po_chr_dev* par, po_chr_dev* par_clone) {
            return false_t;
}

void
    po_chr_dev_del
        (po_chr_dev* par)                           {
            po_del  (&par->dev); cdev_del(&par->chr);
            po_del  (par->type);
}