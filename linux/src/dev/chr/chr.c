#include "chr.h"
#include "type.h"

#include "bit.h"

#include <linux/vmalloc.h>

po_obj_trait po_chr_trait = po_make_trait (
    po_chr_new    ,
    po_chr_clone  ,
    null_t        ,
    po_chr_del    ,
    sizeof(po_chr),
    null_t
);

po_obj_trait *po_chr_t = &po_chr_trait;

bool_t
    po_chr_new
        (po_chr* par_chr, u32_t par_count, va_list par)                              {
            po_str* name = null_t    ; if (par_count > 0) name = va_arg(par, po_str*);
            u64_t   maj  = 0         ; if (par_count > 1) maj  = va_arg(par, u64_t)  ;
            u64_t   min  = shl(1, 19); if (par_count > 2) min  = va_arg(par, u64_t)  ;
            if (po_trait_of(name) != po_str_t)                                         goto new_err;
            if (!po_make_at(&par_chr->name, po_str) from (0))                          goto new_err;
            if (!po_make_at(&par_chr->type, po_set) from (0))                          goto new_err;
            if (alloc_chrdev_region(&par_chr->maj, maj, min, po_str_as_raw(name)) < 0) goto new_err;
            po_str_push_back(&par_chr->name, name);
            par_chr->min = 0;
            return true_t   ;
    new_err:
            po_del(&par_chr->name);
            po_del(&par_chr->type);
            return false_t;
}

bool_t
    po_chr_clone
        (po_chr* par, po_chr* par_clone)  {
            return false_t;
}

void
    po_chr_del
        (po_chr* par)                                      {
            unregister_chrdev_region(par->maj, shl (1, 19));
            po_del(&par->name);
            po_del(&par->type);
}

MODULE_LICENSE("GPL");