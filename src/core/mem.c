#include "mem.h"
#include "macro.h"

po_obj_trait po_mem_trait = po_make_trait (
    po_mem_new    ,
    po_mem_clone  ,
    null_t        ,
    po_mem_del    ,
    sizeof(po_mem),
    null_t
);

po_obj_trait *po_mem_t = &po_mem_trait;

bool_t
    po_mem_new
        (po_mem* par_mem, u32_t par_count, va_list par)                                {
            po_mem_ops *ops = null_t; if (par_count > 0) ops = va_arg(par, po_mem_ops*);
            if (!ops)         return false_t;
            if (!ops->on_acq) return false_t;
            if (!ops->on_rel) return false_t;
            if (!ops->on_new) return false_t;
            if (!ops->on_del) return false_t;

            par_mem->mem = ops->on_new(par_count - 1, par);
            par_mem->ops = ops;

            if (!par_mem->mem) return false_t;
            return true_t;
}

bool_t
    po_mem_clone
        (po_mem* par, po_mem* par_clone) {
            return false_t;
}

void
    po_mem_del
        (po_mem* par)                 {
            par->ops->on_del(par->mem);
}

void*
    po_mem_acq
        (po_mem* par, void* par_hint, u64_t par_len)       {
            if (po_trait_of(par) != po_mem_t) return null_t;
            if (!par_len)                     return null_t;
            return par->ops->on_acq                        (
                par->mem,
                par_hint,
                par_len
            );
}

void
    po_mem_rel
        (po_mem* par, void* par_rel, u64_t par_len) {
            if (po_trait_of(par) != po_mem_t) return;
            if (!par_rel)                     return;
            return par->ops->on_rel                 (
                par->mem,
                par_rel ,
                par_len
            );
}



#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(po_mem_acq);
EXPORT_SYMBOL(po_mem_rel);
EXPORT_SYMBOL(po_mem_t);
#endif