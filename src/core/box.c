#include "box.h"

static bool_t
    do_new
        (pp_box* self, u32_t count, va_list arg)                           {
            u64_t   size = 0ull  ; if (count > 0) size = va_arg(arg, u64_t);
            pp_mem *mem  = null_t; if (count > 1) mem  = va_arg(arg, void*);
            if (pp_trait_of(mem) != pp_mem_t) mem = pp_get_mem();
            if (pp_trait_of(mem) != pp_mem_t) return false_t;
            if (!size)                        return false_t;
            self->ptr = pp_mem_use(mem, null_t, size);

            if (!self->ptr) return false_t;
            self->mem = (pp_mem*) pp_ref (mem);
            self->len = size;
            return true_t;
}

static bool_t
    do_clone
        (pp_box* self, pp_box* clone)                            {
            self->ptr  = pp_mem_use(self->mem, null_t, self->len);

            if (!self->ptr) return false_t;
            self->len = clone->len;
            self->mem = clone->mem;

            pp_mem_copy(self->mem, clone->mem, self->len);
            return true_t;
}

static void
    do_del
        (pp_box* self)                                  {
            pp_mem_free(self->mem, self->ptr, self->len);
            pp_del     (self->mem);
}

static pp_obj_trait
    do_obj = pp_make_trait (
        do_new        ,
        do_clone      ,
        null_t        ,
        do_del        ,
        sizeof(pp_box),
        null_t
);

pp_obj_trait* pp_box_t = &do_obj;

void* pp_box_ptr(pp_box* self) { if (pp_trait_of(self) != pp_box_t) return null_t; return self->mem; }
u64_t pp_box_len(pp_box* self) { if (pp_trait_of(self) != pp_box_t) return 0ull;   return self->len; }

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");
EXPORT_SYMBOL(pp_box_ptr);
EXPORT_SYMBOL(pp_box_len);
EXPORT_SYMBOL(pp_box_t);
#endif