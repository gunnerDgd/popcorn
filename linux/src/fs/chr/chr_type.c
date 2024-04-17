#include "chr_type.h"
#include "chr.h"

#include "../file_type.h"

#include <linux/poll.h>

po_obj_trait po_chr_type_trait = po_make_trait (
    po_chr_type_new    ,
    po_chr_type_clone  ,
    null_t             ,
    po_chr_type_del    ,
    sizeof(po_chr_type),
    null_t
);

po_obj_trait *po_chr_type_t = &po_chr_type_trait;

bool_t
    po_chr_type_new
        (po_chr_type* par_chr, u32_t par_count, va_list par)                         {
            po_str *name = null_t    ; if (par_count > 0) name = va_arg(par, po_str*);
            u64_t   maj  = 0         ; if (par_count > 1) maj  = va_arg(par, u64_t)  ;
            u64_t   num  = shl(1, 19); if (par_count > 2) num  = va_arg(par, u64_t)  ;
            if (po_trait_of (name) != po_str_t) return false_t;
            if (maj >= shl(1, 12))              return false_t;
            if (num >= shl(1, 20))              return false_t;
            ida_init(&par_chr->ida);

            if (alloc_chrdev_region(&par_chr->maj, maj, num, po_str_ptr(name)) < 0) return false_t;
            par_chr->num  = num;
            return true_t;
}

bool_t
    po_chr_type_clone
        (po_chr_type* par, po_chr_type* par_clone)  {
            return false_t;
}

void
    po_chr_type_del
        (po_chr_type* par)                              {
            unregister_chrdev_region(par->maj, par->num);
            ida_destroy             (&par->ida);
}

MODULE_LICENSE("GPL");
EXPORT_SYMBOL(po_chr_type_t);