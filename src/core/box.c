#include "box.h"

po_obj_trait po_box_trait = po_make_trait (
    po_box_new    ,
    po_box_clone  ,
    po_box_ref    ,
    po_box_del    ,
    sizeof(po_box),
    null_t
);

po_obj_trait* po_box_t = &po_box_trait;

bool_t
    po_box_new
        (po_box* self, u32_t count, va_list arg)                           {
            u64_t   size = 0ull  ; if (count > 0) size = va_arg(arg, u64_t);
            po_mem *mem  = null_t; if (count > 1) mem  = va_arg(arg, void*);
            if (po_trait_of(mem) != po_mem_t) mem = po_get_mem();
            if (po_trait_of(mem) != po_mem_t) return false_t;
            if (!size)                        return false_t;
            self->ptr = po_mem_use(mem, null_t, size);

            if (!self->ptr) return false_t;
            self->mem = (po_mem*) po_ref (mem);
            self->len = size;
            return true_t;
}

bool_t
    po_box_clone
        (po_box* self, po_box* clone)                            {
            self->ptr  = po_mem_use(self->mem, null_t, self->len);

            if (!self->ptr) return false_t;
            self->len = clone->len;
            self->mem = clone->mem;

            po_mem_copy(self->mem, clone->mem, self->len);
            return true_t;
}

bool_t
    po_box_ref
        (po_box* self)    {
            return true_t;
}

void
    po_box_del
        (po_box* self)                                  {
            po_mem_free(self->mem, self->ptr, self->len);
            po_del     (self->mem);
}

void*
    po_box_ptr
        (po_box* self)                                      {
            if (po_trait_of(self) != po_box_t) return null_t;
            return self->mem;
}

u64_t
    po_box_len
        (po_box* self)                                 {
            if (po_trait_of(self) != po_box_t) return 0;
            return self->len;
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");
EXPORT_SYMBOL(po_box_ptr);
EXPORT_SYMBOL(po_box_len);
EXPORT_SYMBOL(po_box_t);
#endif