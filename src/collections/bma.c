#include "bma.h"

static bool_t
    do_new
        (pp_bma* self, u32_t count, va_list arg) {
            self->in  = (reg_t) -1;
            self->out = 0;
            return true_t;
}

static bool_t do_clone(pp_bma* self, pp_bma* clone) { return false_t; }
static void   do_del  (pp_bma* self)                {                 }

static pp_obj_trait
    do_obj = pp_make_trait (
        do_new        ,
        do_clone      ,
        null_t        ,
        do_del        ,
        sizeof(pp_bma),
        null_t
);

pp_obj_trait *pp_bma_t = &do_obj;

bool_t
    pp_bma_lock_in
        (pp_bma* self, any_t in)                             {
            if (pp_trait_of(self) != pp_bma_t) return false_t;
            if (!self->in)                     return false_t;
            reg_t pos = pp_bsr(self->in);

            if (!pp_lock_btr(&self->in , pos)) return false_t;
            self->bma[pos] = in;

            if (pp_lock_bts(&self->out, pos)) return false_t;
            return true_t;
}

bool_t
    pp_bma_in
        (pp_bma* self, any_t in)                             {
            if (pp_trait_of(self) != pp_bma_t) return false_t;
            if (!self->in)                     return false_t;
            reg_t pos = pp_bsr (self->in);

            if (!pp_btr(&self->in, pos)) return false_t;
            self->bma[pos] = in;

            pp_bts(&self->out, pos);
            return true_t;
}

bool_t
    pp_bma_lock_out
        (pp_bma* self, any_t* out)                           {
            if (pp_trait_of(self) != pp_bma_t) return false_t;
            if (!out)                          return false_t;
            reg_t pos = pp_bsr (self->out);

            if (!pp_lock_btr(&self->out, pos)) return false_t;
            *out = self->bma[pos];

            if (pp_lock_bts(&self->in , pos)) return false_t;
            return true_t;
}

bool_t
    pp_bma_out
        (pp_bma* self, any_t* out)                           {
            if (pp_trait_of(self) != pp_bma_t) return false_t;
            if (!out)                    return false_t;
            reg_t pos = pp_bsr(self->out);

            if (!pp_btr(&self->out, pos)) return null_t;
            *out = self->bma[pos];

            pp_bts(&self->in , pos);
            return true_t;
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(pp_bma_lock_out);
EXPORT_SYMBOL(pp_bma_lock_in);

EXPORT_SYMBOL(pp_bma_out);
EXPORT_SYMBOL(pp_bma_in);
EXPORT_SYMBOL(pp_bma_t);
#endif