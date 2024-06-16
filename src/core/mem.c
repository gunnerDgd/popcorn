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
        (po_mem* self, u32_t count, va_list arg)                                   {
            po_mem_ops *ops = null_t; if (count > 0) ops = va_arg(arg, po_mem_ops*);
            if (!ops)          return false_t;
            if (!ops->on_use)  return false_t;
            if (!ops->on_free) return false_t;
            if (!ops->on_new)  return false_t;
            if (!ops->on_del)  return false_t;

            self->mem = ops->on_new(count - 1, arg);
            self->ops = ops;

            if (!self->mem) return false_t;
            return true_t;
}

bool_t
    po_mem_clone
        (po_mem* self, po_mem* clone) {
            return false_t;
}

void
    po_mem_del
        (po_mem* self)                  {
            self->ops->on_del(self->mem);
}

void*
    po_mem_use
        (po_mem* self, void* hint, u64_t len)                     {
            if (po_trait_of(self) != po_mem_t) self = po_get_mem();
            if (po_trait_of(self) != po_mem_t) return null_t;
            if (!len)                          return null_t;
            return self->ops->on_use                        (
                self->mem,
                hint,
                len
            );
}

void
    po_mem_free
        (po_mem* self, void* free, u64_t len)        {
            if (po_trait_of(self) != po_mem_t) return;
            if (!free)                         return;
            return self->ops->on_free                (
                self->mem,
                free     ,
                len
            );
}



#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(po_mem_free);
EXPORT_SYMBOL(po_mem_use);
EXPORT_SYMBOL(po_mem_t);
#endif