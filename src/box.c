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
        (po_box* par_box, u32_t par_count, va_list par)                   {
            u64_t   size = 0; if (par_count > 0) size = va_arg(par, u64_t);
            po_mem *res  = 0; if (par_count > 1) res  = va_arg(par, void*);
            if (!res)  res = po_get_mem();
            if (!res)  return false_t;
            if (!size) return false_t;

            par_box->mem  = po_mem_new(res, size);
            par_box->size = size;
            par_box->res  = res ;
            return par_box->mem != 0;
}

bool_t
    po_box_clone
        (po_box* par, po_box* par_clone)       {
            if (!par_clone->mem) return false_t;
            if (!par_clone->res) return false_t;

            par->mem = po_mem_new(par->res, par->size); if (!par->mem) return false_t;
            par->size = par_clone->size;
            par->res  = par_clone->res ;

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
        (po_box* par)           {
            if(!par->res) return;
            if(!par->mem) return;
            po_mem_del(par->res, par->mem);
}

void*
    po_box_ptr
        (po_box* par)                                 {
            if (!par)                         return 0;
            if (po_trait_of(par) != po_box_t) return 0;
            return par->mem;
}

u64_t
    po_box_size
        (po_box* par)                                 {
            if (!par)                         return 0;
            if (po_trait_of(par) != po_box_t) return 0;
            return par->size;
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");
#endif