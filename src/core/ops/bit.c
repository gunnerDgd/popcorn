#include "bit.h"
#include "../obj.h"

struct pp_obj* 
    pp_bit_and(struct pp_obj* self, any_t arg) {
        pp_obj_ops *ops = null_t;
        pp_bit     *bit = null_t;

        if (!pp_trait_of(self)) return null_t; ops = self->trait->ops;
        if (!ops)               return null_t; bit = ops->bit;

        if (!bit->and) return null_t;
        return bit->and(self, arg);
}

struct pp_obj* 
    pp_bit_and_eq(struct pp_obj* self, any_t arg) {
        pp_obj_ops *ops = null_t;
        pp_bit     *bit = null_t;

        if (!pp_trait_of(self)) return null_t; ops = self->trait->ops;
        if (!ops)               return null_t; bit = ops->bit;
        if (!bit->and_eq)       return null_t;

        bit->and_eq(self, arg);
        return self;
}


struct pp_obj* 
    pp_bit_or(struct pp_obj* self, any_t arg) {
        pp_obj_ops *ops = null_t;
        pp_bit     *bit = null_t;

        if (!pp_trait_of(self)) return null_t; ops = self->trait->ops;
        if (!ops)               return null_t; bit = ops->bit;

        if (!bit->or) return null_t;
        return bit->or(self, arg);
}

struct pp_obj* 
    pp_bit_or_eq(struct pp_obj* self, any_t arg) {
        pp_obj_ops *ops = null_t;
        pp_bit     *bit = null_t;

        if (!pp_trait_of(self)) return null_t; ops = self->trait->ops;
        if (!ops)               return null_t; bit = ops->bit;
        if (!bit->or_eq)        return null_t;

        bit->or_eq(self, arg);
        return self;
}


struct pp_obj* 
    pp_bit_xor(struct pp_obj* self, any_t arg) {
        pp_obj_ops *ops = null_t;
        pp_bit     *bit = null_t;

        if (!pp_trait_of(self)) return null_t; ops = self->trait->ops;
        if (!ops)               return null_t; bit = ops->bit;

        if (!bit->xor) return null_t;
        return bit->xor(self, arg);
}

struct pp_obj* 
    pp_bit_xor_eq(struct pp_obj* self, any_t arg) {
        pp_obj_ops *ops = null_t;
        pp_bit     *bit = null_t;

        if (!pp_trait_of(self)) return null_t; ops = self->trait->ops;
        if (!ops)               return null_t; bit = ops->bit;
        if (!bit->xor_eq)       return null_t;

        bit->xor_eq(self, arg);
        return self;
}


struct pp_obj* 
    pp_bit_not(struct pp_obj* self) {
        pp_obj_ops *ops = null_t;
        pp_bit     *bit = null_t;

        if (!pp_trait_of(self)) return null_t; ops = self->trait->ops;
        if (!ops)               return null_t; bit = ops->bit;

        if (!bit->not) return null_t;
        return bit->not(self);
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(pp_bit_and);
EXPORT_SYMBOL(pp_bit_and_eq);
EXPORT_SYMBOL(pp_bit_or);
EXPORT_SYMBOL(pp_bit_or_eq);
EXPORT_SYMBOL(pp_bit_xor);
EXPORT_SYMBOL(pp_bit_xor_eq);
EXPORT_SYMBOL(pp_bit_not);
#endif