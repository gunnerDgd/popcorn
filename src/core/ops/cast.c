#include "cast.h"
#include "../obj.h"

struct pp_obj*
    pp_as(struct pp_obj* par, struct pp_obj_trait* par_trait)      {
        pp_obj       *as    = par       ; if (!as)    return null_t;
        pp_obj_trait *trait = as->trait ; if (!trait) return null_t;
        pp_obj_ops   *ops   = trait->ops; if (!ops)   return null_t;
        
        if (!ops->cast)     return null_t;
        if (!ops->cast->as) return null_t;
        return ops->cast->as(as, par_trait);
}

i8_t
    pp_as_i8(struct pp_obj* par)                              {
        pp_obj       *as    = par       ; if (!as)    return 0;
        pp_obj_trait *trait = as->trait ; if (!trait) return 0;
        pp_obj_ops   *ops   = trait->ops; if (!ops)   return 0;
        if (!ops->cast)        return 0;
        if (!ops->cast->as_i8) return 0;
        return ops->cast->as_i8(as);
}

u8_t
    pp_as_u8(struct pp_obj* par)                              {
        pp_obj       *as    = par       ; if (!as)    return 0;
        pp_obj_trait *trait = as->trait ; if (!trait) return 0;
        pp_obj_ops   *ops   = trait->ops; if (!ops)   return 0;
        if (!ops->cast)        return 0;
        if (!ops->cast->as_u8) return 0;
        return ops->cast->as_u8(as);
}

i16_t
    pp_as_i16(struct pp_obj* par)                             {
        pp_obj       *as    = par       ; if (!as)    return 0;
        pp_obj_trait *trait = as->trait ; if (!trait) return 0;
        pp_obj_ops   *ops   = trait->ops; if (!ops)   return 0;
        if (!ops->cast)         return 0;
        if (!ops->cast->as_i16) return 0;
        return ops->cast->as_i16(as);
}

u16_t
    pp_as_u16(struct pp_obj* par)                             {
        pp_obj       *as    = par       ; if (!as)    return 0;
        pp_obj_trait *trait = as->trait ; if (!trait) return 0;
        pp_obj_ops   *ops   = trait->ops; if (!ops)   return 0;
        if (!ops->cast)         return 0;
        if (!ops->cast->as_u16) return 0;
        return ops->cast->as_u16(as);
}

i32_t
    pp_as_i32(struct pp_obj* par)                             {
        pp_obj       *as    = par       ; if (!as)    return 0;
        pp_obj_trait *trait = as->trait ; if (!trait) return 0;
        pp_obj_ops   *ops   = trait->ops; if (!ops)   return 0;
        if (!ops->cast)         return 0;
        if (!ops->cast->as_i32) return 0;
        return ops->cast->as_i32(as);
}

u32_t
    pp_as_u32(struct pp_obj* par)                             {
        pp_obj       *as    = par       ; if (!as)    return 0;
        pp_obj_trait *trait = as->trait ; if (!trait) return 0;
        pp_obj_ops   *ops   = trait->ops; if (!ops)   return 0;
        if (!ops->cast)         return 0;
        if (!ops->cast->as_u32) return 0;
        return ops->cast->as_u32(as);
}

i64_t
    pp_as_i64(struct pp_obj* par)                             {
        pp_obj       *as    = par       ; if (!as)    return 0;
        pp_obj_trait *trait = as->trait ; if (!trait) return 0;
        pp_obj_ops   *ops   = trait->ops; if (!ops)   return 0;
        if (!ops->cast)         return 0;
        if (!ops->cast->as_i16) return 0;
        return ops->cast->as_i16(as);
}

u64_t
    pp_as_u64(struct pp_obj* par)                             {
        pp_obj       *as    = par       ; if (!as)    return 0;
        pp_obj_trait *trait = as->trait ; if (!trait) return 0;
        pp_obj_ops   *ops   = trait->ops; if (!ops)   return 0;
        if (!ops->cast)         return 0;
        if (!ops->cast->as_u64) return 0;
        return ops->cast->as_u64(as);
}

any_t
    pp_as_any(struct pp_obj* par)                             {
        pp_obj       *as    = par       ; if (!as)    return 0;
        pp_obj_trait *trait = as->trait ; if (!trait) return 0;
        pp_obj_ops   *ops   = trait->ops; if (!ops)   return 0;
        if (!ops->cast)         return 0;
        if (!ops->cast->as_any) return 0;
        return ops->cast->as_any(as);
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");
EXPORT_SYMBOL(pp_as_i8);
EXPORT_SYMBOL(pp_as_i16);
EXPORT_SYMBOL(pp_as_i32);
EXPORT_SYMBOL(pp_as_i64);
EXPORT_SYMBOL(pp_as_u8);
EXPORT_SYMBOL(pp_as_u16);
EXPORT_SYMBOL(pp_as_u32);
EXPORT_SYMBOL(pp_as_u64);
EXPORT_SYMBOL(pp_as);
#endif