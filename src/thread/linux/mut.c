#include "mut.h"

po_obj_trait po_mut_trait = po_make_trait (
    po_mut_new    ,
    po_mut_clone  ,
    null_t        ,
    po_mut_del    ,
    sizeof(po_mut),
    null_t
);

po_obj_trait *po_mut_t = &po_mut_trait;

bool_t
    po_mut_new
        (po_mut* self, u32_t count, va_list arg) {
            mutex_init(&self->mut);
            return true_t;
}

bool_t
    po_mut_clone
        (po_mut* self, po_mut* clone) {
            return false_t;
}

void
    po_mut_del
        (po_mut* self)               {
            mutex_destroy(&self->mut);
}

void
    po_mut_lock
        (po_mut* self)                               {
            if (po_trait_of(self) != po_mut_t) return;
            mutex_lock(&self->mut);
}

bool_t
    po_mut_lock_try
        (po_mut* self)                                       {
            if (po_trait_of(self) != po_mut_t) return false_t;
            return mutex_trylock(&self->mut);
}

void
    po_mut_unlock
        (po_mut* self)                               {
            if (po_trait_of(self) != po_mut_t) return;
            mutex_unlock(&self->mut);
}

#include <linux/module.h>

MODULE_LICENSE("GPL");
EXPORT_SYMBOL(po_mut_unlock)  ;
EXPORT_SYMBOL(po_mut_lock_try);
EXPORT_SYMBOL(po_mut_lock)    ;
EXPORT_SYMBOL(po_mut_t)       ;