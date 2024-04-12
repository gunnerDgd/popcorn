#include "core.h"
#include <linux/slab.h>

struct po_core po_core;

any_t po_heap_do_new(u32_t, va_list);
void  po_heap_do_del(any_t)         ;
void* po_heap_do_acq(any_t, void*, u64_t);
void  po_heap_do_rel(any_t, void*, u64_t);

po_mem_ops po_heap_do = po_make_mem_ops (
    po_heap_do_acq,
    po_heap_do_rel,
    po_heap_do_new,
    po_heap_do_del
);

any_t po_heap_do_new(u32_t par_count, va_list par) { return &po_heap_do; }
void  po_heap_do_del(any_t par)                    { }

void*
    po_heap_do_acq
        (any_t par, void* par_acq, u64_t par_len) {
            if (par != &po_heap_do) return null_t;
            return kmalloc(par_len, GFP_KERNEL);
}

void
    po_heap_do_rel
        (any_t par, void* par_rel, u64_t par_len) {
            if (par != &po_heap_do) return;
            kfree(par_rel);
}

po_mem*
    po_get_mem()          {
        return po_core.mem;
}

po_mem*
    po_set_mem
        (po_mem* par)                                      {
            if (po_trait_of(par) != po_mem_t) return null_t;
            po_mem* ret = po_core.mem;
            po_core.mem = par;
            return  ret;
}

po_obj_trait po_core_trait = po_make_trait (
    po_core_new           ,
    po_core_clone         ,
    po_core_ref           ,
    po_core_del           ,
    sizeof(struct po_core),
    null_t
);

po_obj_trait *po_core_t = &po_core_trait;

bool_t
    po_core_new
        (struct po_core* par_core, u32_t par_count, va_list par)                          {
            if (!po_make_at(&par_core->heap, po_mem) from (1, &po_heap_do)) return false_t;
            par_core->mem = &par_core->heap;
            return true_t;
}

bool_t po_core_clone(struct po_core* par, struct po_core* par_clone) { return     false_t; }
bool_t po_core_ref  (struct po_core* par)                            { return     false_t; }
void   po_core_del  (struct po_core* par)                            { po_del(&par->heap); }
