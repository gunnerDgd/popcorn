#include "arith.h"
#include "../obj.h"

struct po_obj* 
    po_op_add(struct po_obj* par, any_t par_arg)                     {
        po_obj*       add    = par       ; if (!add)    return null_t;
        any_t         arg    = par_arg   ; if (!arg)    return null_t;
        po_obj_trait *trait  = add->trait; if (!trait)  return null_t;
        po_obj_ops   *po_ops = trait->ops; if (!po_ops) return null_t;

        if (!po_ops->arith)      return null_t;
        if (!po_ops->arith->add) return null_t;
        return po_ops->arith->add(add, arg);
}

struct po_obj* 
    po_op_add_eq(struct po_obj* par, any_t par_arg)                  {
        po_obj*       add    = par       ; if (!add)    return null_t;
        any_t         arg    = par_arg   ; if (!arg)    return null_t;
        po_obj_trait *trait  = add->trait; if (!trait)  return null_t;
        po_obj_ops   *po_ops = trait->ops; if (!po_ops) return null_t;

        if (!po_ops->arith)         return null_t;
        if (!po_ops->arith->add_eq) return null_t;
        po_ops->arith->add_eq(add, arg);
        return add;
}


struct po_obj* 
    po_op_sub(struct po_obj* par, any_t par_arg)                     {
        po_obj*       sub    = par       ; if (!sub)    return null_t;
        any_t         arg    = par_arg   ; if (!arg)    return null_t;
        po_obj_trait *trait  = sub->trait; if (!trait)  return null_t;
        po_obj_ops   *po_ops = trait->ops; if (!po_ops) return null_t;

        if (!po_ops->arith)      return null_t;
        if (!po_ops->arith->sub) return null_t;
        return po_ops->arith->sub(sub, arg);
}

struct po_obj* 
    po_op_sub_eq(struct po_obj* par, any_t par_arg)                  {
        po_obj*       sub    = par       ; if (!sub)    return null_t;
        any_t         arg    = par_arg   ; if (!arg)    return null_t;
        po_obj_trait *trait  = sub->trait; if (!trait)  return null_t;
        po_obj_ops   *po_ops = trait->ops; if (!po_ops) return null_t;
        
        if (!po_ops->arith)         return null_t;
        if (!po_ops->arith->sub_eq) return null_t;
        po_ops->arith->sub_eq(sub, arg);
        return sub;
}


struct po_obj* 
    po_op_mul(struct po_obj* par, any_t par_arg)                     {
        po_obj*       mul    = par       ; if (!mul)    return null_t;
        any_t         arg    = par_arg   ; if (!arg)    return null_t;
        po_obj_trait *trait  = mul->trait; if (!trait)  return null_t;
        po_obj_ops   *po_ops = trait->ops; if (!po_ops) return null_t;
        
        if (!po_ops->arith)      return null_t;
        if (!po_ops->arith->mul) return null_t;
        return po_ops->arith->mul(mul, arg);
}

struct po_obj* 
    po_op_mul_eq(struct po_obj* par, any_t par_arg)                  {
        po_obj*       mul    = par       ; if (!mul)    return null_t;
        any_t         arg    = par_arg   ; if (!arg)    return null_t;
        po_obj_trait *trait  = mul->trait; if (!trait)  return null_t;
        po_obj_ops   *po_ops = trait->ops; if (!po_ops) return null_t;
        
        if (!po_ops->arith)         return null_t;
        if (!po_ops->arith->mul_eq) return null_t;
        po_ops->arith->mul_eq(mul, arg);
        return mul;
}


struct po_obj* 
    po_op_div(struct po_obj* par, any_t par_arg)                     {
        po_obj*       div    = par       ; if (!div)    return null_t;
        any_t         arg    = par_arg   ; if (!arg)    return null_t;
        po_obj_trait *trait  = div->trait; if (!trait)  return null_t;
        po_obj_ops   *po_ops = trait->ops; if (!po_ops) return null_t;
        if (!po_ops->arith)      return null_t;
        if (!po_ops->arith->div) return null_t;
        return po_ops->arith->div(div, arg);
}

struct po_obj* 
    po_op_div_eq(struct po_obj* par, any_t par_arg)                  {
        po_obj*       div    = par       ; if (!div)    return null_t;
        any_t         arg    = par_arg   ; if (!arg)    return null_t;
        po_obj_trait *trait  = div->trait; if (!trait)  return null_t;
        po_obj_ops   *po_ops = trait->ops; if (!po_ops) return null_t;
        
        if (!po_ops->arith)         return null_t;
        if (!po_ops->arith->div_eq) return null_t;
        po_ops->arith->div_eq(div, arg);
        return div;
}


struct po_obj* 
    po_op_mod(struct po_obj* par, any_t par_arg)                     {
        po_obj*       mod    = par       ; if (!mod)    return null_t;
        any_t         arg    = par_arg   ; if (!arg)    return null_t;
        po_obj_trait *trait  = mod->trait; if (!trait)  return null_t;
        po_obj_ops   *po_ops = trait->ops; if (!po_ops) return null_t;
        
        if (!po_ops->arith)      return false_t;
        if (!po_ops->arith->mod) return false_t;
        return po_ops->arith->mod(mod, arg);
}

struct po_obj* 
    po_op_mod_eq(struct po_obj* par, any_t par_arg)                  {
        po_obj*       mod    = par       ; if (!mod)    return null_t;
        any_t         arg    = par_arg   ; if (!arg)    return null_t;
        po_obj_trait *trait  = mod->trait; if (!trait)  return null_t;
        po_obj_ops   *po_ops = trait->ops; if (!po_ops) return null_t;
        
        if (!po_ops->arith)         return false_t;
        if (!po_ops->arith->mod_eq) return false_t;
        po_ops->arith->mod_eq(mod, arg);
        return mod;
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");
#endif