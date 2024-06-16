#include "../mem.h"

#include <linux/module.h>
#include <linux/slab.h>

static any_t do_new (u32_t, va_list);
static void  do_del (any_t)         ;
static void  do_free(any_t, void*, u64_t);
static void* do_use (any_t, void*, u64_t);

static po_mem     heap;
static po_mem_ops heap_ops = po_make_mem_ops (
    do_use ,
    do_free,
    do_new ,
    do_del
);

po_mem_ops *po_heap_ops = &heap_ops;
po_mem     *po_heap     = &heap;

any_t do_new(u32_t par_count, va_list par) { return po_heap; }
void  do_del(any_t par)                     { }

void*
    do_use
        (any_t self, void* hint, u64_t len)   {
            if (self != po_heap) return null_t;
            return kzalloc(roundup_pow_of_two(len), GFP_KERNEL);
}

void
    do_free
        (any_t par, void* par_rel, u64_t par_len) {
            if (par != po_heap) return;
            kfree(par_rel);
}

MODULE_LICENSE("GPL");
EXPORT_SYMBOL(po_heap_ops);
EXPORT_SYMBOL(po_heap);