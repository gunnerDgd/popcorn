#include "cast.h"
#include "../obj.h"

struct po_obj*
    po_as(struct po_obj* par, struct po_obj_trait* par_trait)      {
        po_obj       *as    = par       ; if (!as)    return null_t;
        po_obj_trait *trait = as->trait ; if (!trait) return null_t;
        po_obj_ops   *ops   = trait->ops; if (!ops)   return null_t;
        
        if (!ops->cast)     return null_t;
        if (!ops->cast->as) return null_t;
        return ops->cast->as(as, par_trait);
}

i8_t
    po_as_i8(struct po_obj* par)                              {
        po_obj       *as    = par       ; if (!as)    return 0;
        po_obj_trait *trait = as->trait ; if (!trait) return 0;
        po_obj_ops   *ops   = trait->ops; if (!ops)   return 0;
        if (!ops->cast)        return 0;
        if (!ops->cast->as_i8) return 0;
        return ops->cast->as_i8(as);
}

u8_t
    po_as_u8(struct po_obj* par)                              {
        po_obj       *as    = par       ; if (!as)    return 0;
        po_obj_trait *trait = as->trait ; if (!trait) return 0;
        po_obj_ops   *ops   = trait->ops; if (!ops)   return 0;
        if (!ops->cast)        return 0;
        if (!ops->cast->as_u8) return 0;
        return ops->cast->as_u8(as);
}

i16_t
    po_as_i16(struct po_obj* par)                             {
        po_obj       *as    = par       ; if (!as)    return 0;
        po_obj_trait *trait = as->trait ; if (!trait) return 0;
        po_obj_ops   *ops   = trait->ops; if (!ops)   return 0;
        if (!ops->cast)         return 0;
        if (!ops->cast->as_i16) return 0;
        return ops->cast->as_i16(as);
}

u16_t
    po_as_u16(struct po_obj* par)                             {
        po_obj       *as    = par       ; if (!as)    return 0;
        po_obj_trait *trait = as->trait ; if (!trait) return 0;
        po_obj_ops   *ops   = trait->ops; if (!ops)   return 0;
        if (!ops->cast)         return 0;
        if (!ops->cast->as_u16) return 0;
        return ops->cast->as_u16(as);
}

i32_t
    po_as_i32(struct po_obj* par)                             {
        po_obj       *as    = par       ; if (!as)    return 0;
        po_obj_trait *trait = as->trait ; if (!trait) return 0;
        po_obj_ops   *ops   = trait->ops; if (!ops)   return 0;
        if (!ops->cast)         return 0;
        if (!ops->cast->as_i32) return 0;
        return ops->cast->as_i32(as);
}

u32_t
    po_as_u32(struct po_obj* par)                             {
        po_obj       *as    = par       ; if (!as)    return 0;
        po_obj_trait *trait = as->trait ; if (!trait) return 0;
        po_obj_ops   *ops   = trait->ops; if (!ops)   return 0;
        if (!ops->cast)         return 0;
        if (!ops->cast->as_u32) return 0;
        return ops->cast->as_u32(as);
}

i64_t
    po_as_i64(struct po_obj* par)                             {
        po_obj       *as    = par       ; if (!as)    return 0;
        po_obj_trait *trait = as->trait ; if (!trait) return 0;
        po_obj_ops   *ops   = trait->ops; if (!ops)   return 0;
        if (!ops->cast)         return 0;
        if (!ops->cast->as_i16) return 0;
        return ops->cast->as_i16(as);
}

u64_t
    po_as_u64(struct po_obj* par)                             {
        po_obj       *as    = par       ; if (!as)    return 0;
        po_obj_trait *trait = as->trait ; if (!trait) return 0;
        po_obj_ops   *ops   = trait->ops; if (!ops)   return 0;
        if (!ops->cast)         return 0;
        if (!ops->cast->as_u64) return 0;
        return ops->cast->as_u64(as);
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");
#endif