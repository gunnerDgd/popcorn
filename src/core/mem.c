#include "mem.h"
#include "macro.h"

static bool_t
    do_new
        (pp_mem* self, u32_t count, va_list arg)                                   {
            pp_mem_ops *ops = null_t; if (count > 0) ops = va_arg(arg, pp_mem_ops*);
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

static bool_t
    do_clone
        (pp_mem* self, pp_mem* clone) {
            return false_t;
}

static void
    do_del
        (pp_mem* self)                  {
            self->ops->on_del(self->mem);
}

static pp_obj_trait
    do_obj = pp_make_trait (
        do_new        ,
        do_clone      ,
        null_t        ,
        do_del        ,
        sizeof(pp_mem),
        null_t
);

pp_obj_trait *pp_mem_t = &do_obj;

void*
    pp_mem_use
        (pp_mem* self, void* hint, u64_t len)                     {
            if (pp_trait_of(self) != pp_mem_t) self = pp_get_mem();
            if (pp_trait_of(self) != pp_mem_t) return null_t;
            if (!len)                          return null_t;
            return self->ops->on_use                        (
                self->mem,
                hint,
                len
            );
}

void
    pp_mem_free
        (pp_mem* self, void* free, u64_t len)        {
            if (pp_trait_of(self) != pp_mem_t) return;
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

EXPORT_SYMBOL(pp_mem_free);
EXPORT_SYMBOL(pp_mem_use);
EXPORT_SYMBOL(pp_mem_t);
#endif