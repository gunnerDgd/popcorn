#include "bma.h"

po_obj_trait po_bma_trait = po_make_trait (
    po_bma_new    ,
    po_bma_clone  ,
    null_t        ,
    po_bma_del    ,
    sizeof(po_bma),
    null_t
);

po_obj_trait *po_bma_t = &po_bma_trait;

bool_t
    po_bma_new
        (po_bma* self, u32_t count, va_list arg) {
            self->in  = (reg_t) -1;
            self->out = 0;
            return true_t;
}

bool_t po_bma_clone(po_bma* self, po_bma* clone) { return false_t; }
void   po_bma_del  (po_bma* self)                {                 }

bool_t
    po_bma_in_lock
        (po_bma* self, any_t in)                             {
            if (po_trait_of(self) != po_bma_t) return false_t;
            if (!self->in)                     return false_t;
            u64_t pos = po_bsr64 (self->in);

            if (!po_lock_btr64(&self->in , pos)) return false_t;
            self->bma[pos] = in;

            if (po_lock_bts64(&self->out, pos)) return false_t;
            return true_t;
}

bool_t
    po_bma_in
        (po_bma* self, any_t in)                             {
            if (po_trait_of(self) != po_bma_t) return false_t;
            if (!self->in)                     return false_t;
            u64_t pos = po_bsr64 (self->in);

            if (!po_btr64(&self->in , pos)) return false_t;
            self->bma[pos] = in;

            po_bts64(&self->out, pos);
            return true_t;
}

bool_t
    po_bma_out_lock
        (po_bma* self, any_t* out)                           {
            if (po_trait_of(self) != po_bma_t) return false_t;
            if (!out)                          return false_t;
            u64_t pos = po_bsr64 (self->out);

            if (!po_lock_btr64(&self->out, pos)) return false_t;
            *out = self->bma[pos];

            if (po_lock_bts64(&self->in , pos)) return false_t;
            return true_t;
}

bool_t
    po_bma_out
        (po_bma* self, any_t* out)                           {
            if (po_trait_of(self) != po_bma_t) return false_t;
            if (!out)                    return false_t;
            u64_t pos = po_bsr64 (self->out);

            if (!po_btr64(&self->out, pos)) return null_t;
            *out = self->bma[pos];

            po_bts64(&self->in , pos);
            return true_t;
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(po_bma_out_lock);
EXPORT_SYMBOL(po_bma_out);
EXPORT_SYMBOL(po_bma_in_lock);
EXPORT_SYMBOL(po_bma_in);
EXPORT_SYMBOL(po_bma_t);
#endif