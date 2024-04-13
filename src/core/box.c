#include "box.h"

po_obj_trait po_box_trait = po_make_trait (
    po_box_new    ,
    po_box_clone  ,
    po_box_ref    ,
    po_box_del    ,
    sizeof(po_box),
    null_t
);

po_obj_trait* po_box_t = &po_box_trait;

bool_t
    po_box_new
        (po_box* par_box, u32_t par_count, va_list par)                        {
            u64_t   size = 0ull  ; if (par_count > 0) size = va_arg(par, u64_t);
            po_mem *mem  = null_t; if (par_count > 1) mem  = va_arg(par, void*);
            if (po_trait_of(mem) != po_mem_t) mem = po_get_mem();
            if (po_trait_of(mem) != po_mem_t) return false_t;
            if (!size)                        return false_t;

            par_box->ptr  = po_mem_acq(mem, null_t, size); if (!par_box->ptr) return false_t;
            par_box->mem  = (po_mem*) po_ref (mem);
            par_box->size = size;
            return true_t;
}

bool_t
    po_box_clone
        (po_box* par, po_box* par_clone)                                                      {
            par->ptr  = po_mem_acq(par->mem, null_t, par->size); if (!par->ptr) return false_t;
            par->size = par_clone->size;
            par->mem  = par_clone->mem ;

            po_mem_copy(par->mem, par_clone->mem, par->size);
            return true_t;
}

bool_t
    po_box_ref
        (po_box* par)    {
            return true_t;
}

void
    po_box_del
        (po_box* par)                                {
            po_mem_rel(par->mem, par->ptr, par->size);
            po_del    (par->mem);
}

void*
    po_box_ptr
        (po_box* par)                                 {
            if (po_trait_of(par) != po_box_t) return 0;
            return par->mem;
}

u64_t
    po_box_size
        (po_box* par)                                 {
            if (po_trait_of(par) != po_box_t) return 0;
            return par->size;
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");
EXPORT_SYMBOL(po_box_ptr);
EXPORT_SYMBOL(po_box_size);
EXPORT_SYMBOL(po_box_t);
#endif