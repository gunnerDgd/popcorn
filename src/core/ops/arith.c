#include "arith.h"
#include "../obj.h"

struct pp_obj* 
    pp_add(struct pp_obj* self, any_t arg)   {
        pp_obj_ops *ops = null_t;
        pp_arith   *ari = null_t;

        if (!pp_trait_of(self)) return null_t; ops = self->trait->ops;
        if (!ops)               return null_t; ari = ops->arith;

        if (!ari->add) return null_t;
        return ari->add(self, arg);
}

struct pp_obj* 
    pp_add_eq(struct pp_obj* self, any_t arg) {
        pp_obj_ops *ops = null_t;
        pp_arith   *ari = null_t;

        if (!pp_trait_of(self)) return null_t; ops = self->trait->ops;
        if (!ops)               return null_t; ari = ops->arith;
        if (!ari->add_eq)       return null_t;

        ari->add_eq(self, arg);
        return self;
}


struct pp_obj* 
    pp_sub(struct pp_obj* self, any_t arg) {
        pp_obj_ops *ops = null_t;
        pp_arith   *ari = null_t;

        if (!pp_trait_of(self)) return null_t; ops = self->trait->ops;
        if (!ops)               return null_t; ari = ops->arith;

        if (!ari->sub) return null_t;
        return ari->sub(self, arg);
}

struct pp_obj* 
    pp_sub_eq(struct pp_obj* self, any_t arg) {
        pp_obj_ops *ops = null_t;
        pp_arith   *ari = null_t;

        if (!pp_trait_of(self)) return null_t; ops = self->trait->ops;
        if (!ops)               return null_t; ari = ops->arith;
        if (!ari->sub_eq)       return null_t;

        ari->sub_eq(self, arg);
        return self;
}


struct pp_obj* 
    pp_mul(struct pp_obj* self, any_t arg) {
        pp_obj_ops *ops = null_t;
        pp_arith   *ari = null_t;

        if (!pp_trait_of(self)) return null_t; ops = self->trait->ops;
        if (!ops)               return null_t; ari = ops->arith;

        if (!ari->mul) return null_t;
        return ari->mul(self, arg);
}

struct pp_obj* 
    pp_mul_eq(struct pp_obj* self, any_t arg) {
        pp_obj_ops *ops = null_t;
        pp_arith   *ari = null_t;

        if (!pp_trait_of(self)) return null_t; ops = self->trait->ops;
        if (!ops)               return null_t; ari = ops->arith;
        if (!ari->mul_eq)       return null_t;

        ari->mul_eq(self, arg);
        return self;
}


struct pp_obj* 
    pp_div(struct pp_obj* self, any_t arg) {
        pp_obj_ops *ops = null_t;
        pp_arith   *ari = null_t;

        if (!pp_trait_of(self)) return null_t; ops = self->trait->ops;
        if (!ops)               return null_t; ari = ops->arith;

        if (!ari->div) return null_t;
        return ari->div(self, arg);
}

struct pp_obj* 
    pp_div_eq(struct pp_obj* self, any_t arg) {
        pp_obj_ops *ops = null_t;
        pp_arith   *ari = null_t;

        if (!pp_trait_of(self)) return null_t; ops = self->trait->ops;
        if (!ops)               return null_t; ari = ops->arith;
        if (!ari->div_eq)       return null_t;

        ari->div_eq(self, arg);
        return self;
}


struct pp_obj* 
    pp_mod(struct pp_obj* self, any_t arg) {
        pp_obj_ops *ops = null_t;
        pp_arith   *ari = null_t;

        if (!pp_trait_of(self)) return null_t; ops = self->trait->ops;
        if (!ops)               return null_t; ari = ops->arith;

        if (!ari->mod) return null_t;
        return ari->mod(self, arg);
}

struct pp_obj* 
    pp_mod_eq(struct pp_obj* self, any_t arg) {
        pp_obj_ops *ops = null_t;
        pp_arith   *ari = null_t;

        if (!pp_trait_of(self)) return null_t; ops = self->trait->ops;
        if (!ops)               return null_t; ari = ops->arith;
        if (!ari->mod_eq)       return null_t;

        ari->mod_eq(self, arg);
        return self;
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(pp_mod_eq);
EXPORT_SYMBOL(pp_mod);
EXPORT_SYMBOL(pp_add);
EXPORT_SYMBOL(pp_add_eq);
EXPORT_SYMBOL(pp_sub);
EXPORT_SYMBOL(pp_sub_eq);
EXPORT_SYMBOL(pp_mul);
EXPORT_SYMBOL(pp_mul_eq);
EXPORT_SYMBOL(pp_div);
EXPORT_SYMBOL(pp_div_eq);
#endif