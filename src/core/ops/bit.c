#include "bit.h"
#include "../obj.h"

struct po_obj* 
    po_op_and(struct po_obj* par, any_t par_arg)                     {
        po_obj*       and    = par       ; if (!and)    return null_t;
        any_t         arg    = par_arg   ; if (!arg)    return null_t;
        po_obj_trait *trait  = and->trait; if (!trait)  return null_t;
        po_obj_ops   *po_ops = trait->ops; if (!po_ops) return null_t;

        if (!po_ops->bit)      return null_t;
        if (!po_ops->bit->and) return null_t;
        return po_ops->bit->and(and, arg);
}

struct po_obj* 
    po_op_and_eq(struct po_obj* par, any_t par_arg)                  {
        po_obj*       and    = par       ; if (!and)    return null_t;
        any_t         arg    = par_arg   ; if (!arg)    return null_t;
        po_obj_trait *trait  = and->trait; if (!trait)  return null_t;
        po_obj_ops   *po_ops = trait->ops; if (!po_ops) return null_t;

        if (!po_ops->bit)         return null_t;
        if (!po_ops->bit->and_eq) return null_t;
        po_ops->bit->and(and, arg);
        return and;
}


struct po_obj* 
    po_op_or(struct po_obj* par, any_t par_arg)                      {
        po_obj*       or     = par       ; if (!or)     return null_t;
        any_t         arg    = par_arg   ; if (!arg)    return null_t;
        po_obj_trait *trait  = or->trait ; if (!trait)  return null_t;
        po_obj_ops   *po_ops = trait->ops; if (!po_ops) return null_t;

        if (!po_ops->bit)     return null_t;
        if (!po_ops->bit->or) return null_t;
        return po_ops->bit->or(or, arg);
}

struct po_obj* 
    po_op_or_eq(struct po_obj* par, any_t par_arg)                   {
        po_obj*       or     = par       ; if (!or)     return null_t;
        any_t         arg    = par_arg   ; if (!arg)    return null_t;
        po_obj_trait *trait  = or->trait ; if (!trait)  return null_t;
        po_obj_ops   *po_ops = trait->ops; if (!po_ops) return null_t;
        
        if (!po_ops->bit)        return null_t;
        if (!po_ops->bit->or_eq) return null_t;
        po_ops->bit->or(or, arg);
        return or;
}


struct po_obj* 
    po_op_xor(struct po_obj* par, any_t par_arg)                     {
        po_obj*       xor    = par       ; if (!xor)    return null_t;
        any_t         arg    = par_arg   ; if (!arg)    return null_t;
        po_obj_trait *trait  = xor->trait; if (!trait)  return null_t;
        po_obj_ops   *po_ops = trait->ops; if (!po_ops) return null_t;
        
        if (!po_ops->bit)      return null_t;
        if (!po_ops->bit->xor) return null_t;
        return po_ops->bit->xor(xor, arg);
}

struct po_obj* 
    po_op_xor_eq(struct po_obj* par, any_t par_arg)                  {
        po_obj*       xor    = par       ; if (!xor)    return null_t;
        any_t         arg    = par_arg   ; if (!arg)    return null_t;
        po_obj_trait *trait  = xor->trait; if (!trait)  return null_t;
        po_obj_ops   *po_ops = trait->ops; if (!po_ops) return null_t;
        
        if (!po_ops->bit)         return null_t;
        if (!po_ops->bit->xor_eq) return null_t;
        po_ops->bit->xor_eq(xor, arg);
        return xor;
}


struct po_obj* 
    po_op_not(struct po_obj* par)                                    {
        po_obj*       not    = par       ; if (!not)    return null_t;
        po_obj_trait *trait  = not->trait; if (!trait)  return null_t;
        po_obj_ops   *po_ops = trait->ops; if (!po_ops) return null_t;
        if (!po_ops->bit)      return null_t;
        if (!po_ops->bit->not) return null_t;
        return po_ops->bit->not(not);
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");
#endif