#include "core.h"
#include <linux/slab.h>

struct po_core po_core;

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");
#endif

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
        (struct po_core* self, u32_t count, va_list arg)                                        {
            if (!po_make_at(po_heap_atomic, po_mem) from (1, po_heap_ops_atomic)) return false_t;
            if (!po_make_at(po_heap       , po_mem) from (1, po_heap_ops))        return false_t;
            po_set_mem(po_heap);
            return true_t;
}

bool_t po_core_clone(struct po_core* self, struct po_core* clone) { return false_t; }
bool_t po_core_ref  (struct po_core* self)                        { return false_t; }

void
    po_core_del
        (struct po_core* self)    {
            po_del(po_heap_atomic);
            po_del(po_heap);
}
