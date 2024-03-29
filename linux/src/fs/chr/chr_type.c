#include "chr_type.h"
#include "chr.h"

#include "../file_type.h"
#include "../../sync/not.h"

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
        (po_chr_type* par_chr, u32_t par_count, va_list par) {
            cstr_t name = cstr_from_va(par);
            if (!name.str) return false_t;
            if (!name.len) return false_t;

            po_file_type *type = null_t    ; if (par_count > 2) type = va_arg(par, po_file_type*);
            u64_t         maj  = 0         ; if (par_count > 3) maj  = va_arg(par, u64_t)        ;
            u64_t         num  = shl(1, 19); if (par_count > 4) num  = va_arg(par, u64_t)        ;
            if (po_trait_of (type) != po_file_type_t) return false_t;
            if (maj >= shl(1, 12))                    return false_t;
            if (num >= shl(1, 20))                    return false_t;
            ida_init(&par_chr->ida);

            if (alloc_chrdev_region(&par_chr->maj, maj, num, name.str) < 0) return false_t;
            par_chr->type = (po_file_type*) po_ref(type);
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
            po_del                  (par->type);
}

MODULE_LICENSE("GPL");