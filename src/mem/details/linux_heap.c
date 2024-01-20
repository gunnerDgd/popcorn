#include "linux_heap.h"

#include <linux/slab.h>
#include <linux/vmalloc.h>

void* po_heap_new       (po_mem* par, u64_t par_size) { return kzalloc(par_size, GFP_KERNEL); }
void  po_heap_del       (po_mem* par, void* par_mem)  { kfree(par_mem); }

void* po_heap_atomic_new(po_mem* par, u64_t par_size) { return kzalloc(par_size, GFP_ATOMIC); }
void  po_heap_atomic_del(po_mem* par, void* par_mem)  { kfree(par_mem); }

po_mem po_heap =             {
    .on_new    = &po_heap_new,
    .on_del    = &po_heap_del
};

po_mem po_heap_atomic =                    {
    .on_new           = &po_heap_atomic_new,
    .on_del           = &po_heap_atomic_del
};