#include "bit.h"
#include "../obj.h"

struct pp_obj* 
    pp_bit_and(struct pp_obj* par, any_t par_arg)                     {
        pp_obj*       and    = par       ; if (!and)    return null_t;
        any_t         arg    = par_arg   ; if (!arg)    return null_t;
        pp_obj_trait *trait  = and->trait; if (!trait)  return null_t;
        pp_obj_ops   *pp_ops = trait->ops; if (!pp_ops) return null_t;

        if (!pp_ops->bit)      return null_t;
        if (!pp_ops->bit->and) return null_t;
        return pp_ops->bit->and(and, arg);
}

struct pp_obj* 
    pp_bit_and_eq(struct pp_obj* par, any_t par_arg)                  {
        pp_obj*       and    = par       ; if (!and)    return null_t;
        any_t         arg    = par_arg   ; if (!arg)    return null_t;
        pp_obj_trait *trait  = and->trait; if (!trait)  return null_t;
        pp_obj_ops   *pp_ops = trait->ops; if (!pp_ops) return null_t;

        if (!pp_ops->bit)         return null_t;
        if (!pp_ops->bit->and_eq) return null_t;
        pp_ops->bit->and(and, arg);
        return and;
}


struct pp_obj* 
    pp_bit_or(struct pp_obj* par, any_t par_arg)                      {
        pp_obj*       or     = par       ; if (!or)     return null_t;
        any_t         arg    = par_arg   ; if (!arg)    return null_t;
        pp_obj_trait *trait  = or->trait ; if (!trait)  return null_t;
        pp_obj_ops   *pp_ops = trait->ops; if (!pp_ops) return null_t;

        if (!pp_ops->bit)     return null_t;
        if (!pp_ops->bit->or) return null_t;
        return pp_ops->bit->or(or, arg);
}

struct pp_obj* 
    pp_bit_or_eq(struct pp_obj* par, any_t par_arg)                   {
        pp_obj*       or     = par       ; if (!or)     return null_t;
        any_t         arg    = par_arg   ; if (!arg)    return null_t;
        pp_obj_trait *trait  = or->trait ; if (!trait)  return null_t;
        pp_obj_ops   *pp_ops = trait->ops; if (!pp_ops) return null_t;
        
        if (!pp_ops->bit)        return null_t;
        if (!pp_ops->bit->or_eq) return null_t;
        pp_ops->bit->or(or, arg);
        return or;
}


struct pp_obj* 
    pp_bit_xor(struct pp_obj* par, any_t par_arg)                     {
        pp_obj*       xor    = par       ; if (!xor)    return null_t;
        any_t         arg    = par_arg   ; if (!arg)    return null_t;
        pp_obj_trait *trait  = xor->trait; if (!trait)  return null_t;
        pp_obj_ops   *pp_ops = trait->ops; if (!pp_ops) return null_t;
        
        if (!pp_ops->bit)      return null_t;
        if (!pp_ops->bit->xor) return null_t;
        return pp_ops->bit->xor(xor, arg);
}

struct pp_obj* 
    pp_bit_xor_eq(struct pp_obj* par, any_t par_arg)                  {
        pp_obj*       xor    = par       ; if (!xor)    return null_t;
        any_t         arg    = par_arg   ; if (!arg)    return null_t;
        pp_obj_trait *trait  = xor->trait; if (!trait)  return null_t;
        pp_obj_ops   *pp_ops = trait->ops; if (!pp_ops) return null_t;
        
        if (!pp_ops->bit)         return null_t;
        if (!pp_ops->bit->xor_eq) return null_t;
        pp_ops->bit->xor_eq(xor, arg);
        return xor;
}


struct pp_obj* 
    pp_bit_not(struct pp_obj* par)                                    {
        pp_obj*       not    = par       ; if (!not)    return null_t;
        pp_obj_trait *trait  = not->trait; if (!trait)  return null_t;
        pp_obj_ops   *pp_ops = trait->ops; if (!pp_ops) return null_t;
        if (!pp_ops->bit)      return null_t;
        if (!pp_ops->bit->not) return null_t;
        return pp_ops->bit->not(not);
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