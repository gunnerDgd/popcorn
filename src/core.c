#include "core.h"
#include <linux/slab.h>

struct pp pp;

static bool_t
    do_new
        (struct pp* self, u32_t count, va_list arg)                                             {
            if (!pp_make_at(pp_heap_atomic, pp_mem) from (1, pp_heap_ops_atomic)) return false_t;
            if (!pp_make_at(pp_heap       , pp_mem) from (1, pp_heap_ops))        return false_t;
            pp_set_mem(pp_heap);
            return true_t;
}

static bool_t
    do_clone
        (struct pp* self, struct pp* clone) {
            return false_t;
}

static bool_t
    do_ref
        (struct pp* self) {
            return false_t;
}

static void
    do_del
        (struct po* self)         {
            pp_del(pp_heap_atomic);
            pp_del(pp_heap);
}

static pp_obj_trait
    do_obj = pp_make_trait (
        do_new           ,
        do_clone         ,
        do_ref           ,
        do_del           ,
        sizeof(struct pp),
        null_t
);

pp_obj_trait *pp_t = &do_obj;

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");
EXPORT_SYMBOL(pp_t);
#endif