#include "po.h"
#include <linux/slab.h>

struct po po;

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");
#endif

static bool_t
    do_new
        (struct po* self, u32_t count, va_list arg)                                        {
            if (!po_make_at(po_heap_atomic, po_mem) from (1, po_heap_ops_atomic)) return false_t;
            if (!po_make_at(po_heap       , po_mem) from (1, po_heap_ops))        return false_t;
            po_set_mem(po_heap);
            return true_t;
}

static bool_t
    do_clone
        (struct po* self, struct po* clone) {
            return false_t;
}

static bool_t
    do_ref
        (struct po* self) {
            return false_t;
}

void
    do_del
        (struct po* self)         {
            po_del(po_heap_atomic);
            po_del(po_heap);
}

po_obj_trait po_trait = po_make_trait (
    do_new           ,
    do_clone         ,
    do_ref           ,
    do_del           ,
    sizeof(struct po),
    null_t
);

po_obj_trait *po_t = &po_trait;