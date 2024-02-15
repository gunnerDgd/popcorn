#include "../mem.h"

#include <linux/module.h>
#include <linux/string.h>

#include <linux/slab.h>
#include <linux/vmalloc.h>

void  po_mem_set (void* par, u8_t par_set, u64_t par_size)                    { memset (par, par_set, par_size); }
void  po_mem_copy(void* par, void* par_src, u64_t par_size)                   { memcpy (par, par_src, par_size); }
void  po_mem_move(void* par, void* par_src, u64_t par_size)                   { memmove(par, par_src, par_size); }
u64_t po_mem_find(void* par, void* par_cmp, u64_t par_len, u64_t par_cmp_len) { return (u64_t) strnstr(par, par_cmp, par_len); }

bool_t po_mem_eq(void* par, void* par_cmp, u64_t par_size) { return strncmp(par, par_cmp, par_size) == 0; }
bool_t po_mem_gt(void* par, void* par_cmp, u64_t par_size) { return strncmp(par, par_cmp, par_size) >  0; }
bool_t po_mem_lt(void* par, void* par_cmp, u64_t par_size) { return strncmp(par, par_cmp, par_size) <  0; }

void*
    po_heap_new
        (po_mem* par, u64_t par_size)         {
            if (par != &po_heap) return null_t;
            return kmalloc                    (
                par_size ,
                GFP_KERNEL
            );
}

void
    po_heap_free
        (po_mem* par, void* par_mem)   {
            if (par != &po_heap) return;
            kfree(par_mem);
}

void*
    po_heap_atom_new
        (po_mem* par, u64_t par_size)         {
            if (par != &po_heap) return null_t;
            return kmalloc                    (
                par_size ,
                GFP_ATOMIC
            );
}

void
    po_heap_atom_free
        (po_mem* par, void* par_mem)   {
            if (par != &po_heap) return;
            kfree(par_mem);
}

void*
    po_page_new
        (po_mem* par, u64_t par_size)         {
            if (par != &po_heap) return null_t;
            return vmalloc(par_size);
}

void
    po_page_free
        (po_mem* par, void* par_mem)   {
            if (par != &po_heap) return;
            vfree(par_mem);
}

po_mem po_heap =             {
    .on_new    = po_heap_new ,
    .on_del    = po_heap_free
};

po_mem po_heap_atom =                  {
    .on_new         = po_heap_atom_new ,
    .on_del         = po_heap_atom_free
};

po_mem po_page =             {
    .on_new    = po_page_new ,
    .on_del    = po_page_free
};

MODULE_LICENSE("GPL");