#include "../mem.h"

#include <linux/module.h>
#include <linux/slab.h>

static any_t do_new (u32_t, va_list);
static void  do_del (any_t)         ;
static void  do_free(any_t, void*, u64_t);
static void* do_use (any_t, void*, u64_t);

static po_mem     heap_atomic;
static po_mem_ops heap_ops_atomic = po_make_mem_ops (
    do_use ,
    do_free,
    do_new ,
    do_del
);

po_mem_ops *po_heap_ops_atomic = &heap_ops_atomic;
po_mem     *po_heap_atomic     = &heap_atomic;

any_t do_new(u32_t par_count, va_list par) { return po_heap_atomic; }
void  do_del(any_t par)                     { }

void*
    do_use
        (any_t self, void* hint, u64_t len)          {
            if (self != po_heap_atomic) return null_t;
            return kzalloc(roundup_pow_of_two(len), GFP_ATOMIC);
}

void
    do_free
        (any_t self, void* free, u64_t len) {
            if (self != po_heap_atomic) return;
            kfree(free);
}

MODULE_LICENSE("GPL");
EXPORT_SYMBOL(po_heap_ops_atomic);
EXPORT_SYMBOL(po_heap_atomic);