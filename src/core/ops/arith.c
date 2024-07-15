#include "arith.h"
#include "../obj.h"

struct pp_obj* 
    pp_add(struct pp_obj* par, any_t par_arg)                     {
        pp_obj*       add    = par       ; if (!add)    return null_t;
        any_t         arg    = par_arg   ; if (!arg)    return null_t;
        pp_obj_trait *trait  = add->trait; if (!trait)  return null_t;
        pp_obj_ops   *pp_ops = trait->ops; if (!pp_ops) return null_t;

        if (!pp_ops->arith)      return null_t;
        if (!pp_ops->arith->add) return null_t;
        return pp_ops->arith->add(add, arg);
}

struct pp_obj* 
    pp_add_eq(struct pp_obj* par, any_t par_arg)                  {
        pp_obj*       add    = par       ; if (!add)    return null_t;
        any_t         arg    = par_arg   ; if (!arg)    return null_t;
        pp_obj_trait *trait  = add->trait; if (!trait)  return null_t;
        pp_obj_ops   *pp_ops = trait->ops; if (!pp_ops) return null_t;

        if (!pp_ops->arith)         return null_t;
        if (!pp_ops->arith->add_eq) return null_t;
        pp_ops->arith->add_eq(add, arg);
        return add;
}


struct pp_obj* 
    pp_sub(struct pp_obj* par, any_t par_arg)                     {
        pp_obj*       sub    = par       ; if (!sub)    return null_t;
        any_t         arg    = par_arg   ; if (!arg)    return null_t;
        pp_obj_trait *trait  = sub->trait; if (!trait)  return null_t;
        pp_obj_ops   *pp_ops = trait->ops; if (!pp_ops) return null_t;

        if (!pp_ops->arith)      return null_t;
        if (!pp_ops->arith->sub) return null_t;
        return pp_ops->arith->sub(sub, arg);
}

struct pp_obj* 
    pp_sub_eq(struct pp_obj* par, any_t par_arg)                  {
        pp_obj*       sub    = par       ; if (!sub)    return null_t;
        any_t         arg    = par_arg   ; if (!arg)    return null_t;
        pp_obj_trait *trait  = sub->trait; if (!trait)  return null_t;
        pp_obj_ops   *pp_ops = trait->ops; if (!pp_ops) return null_t;
        
        if (!pp_ops->arith)         return null_t;
        if (!pp_ops->arith->sub_eq) return null_t;
        pp_ops->arith->sub_eq(sub, arg);
        return sub;
}


struct pp_obj* 
    pp_mul(struct pp_obj* par, any_t par_arg)                     {
        pp_obj*       mul    = par       ; if (!mul)    return null_t;
        any_t         arg    = par_arg   ; if (!arg)    return null_t;
        pp_obj_trait *trait  = mul->trait; if (!trait)  return null_t;
        pp_obj_ops   *pp_ops = trait->ops; if (!pp_ops) return null_t;
        
        if (!pp_ops->arith)      return null_t;
        if (!pp_ops->arith->mul) return null_t;
        return pp_ops->arith->mul(mul, arg);
}

struct pp_obj* 
    pp_mul_eq(struct pp_obj* par, any_t par_arg)                  {
        pp_obj*       mul    = par       ; if (!mul)    return null_t;
        any_t         arg    = par_arg   ; if (!arg)    return null_t;
        pp_obj_trait *trait  = mul->trait; if (!trait)  return null_t;
        pp_obj_ops   *pp_ops = trait->ops; if (!pp_ops) return null_t;
        
        if (!pp_ops->arith)         return null_t;
        if (!pp_ops->arith->mul_eq) return null_t;
        pp_ops->arith->mul_eq(mul, arg);
        return mul;
}


struct pp_obj* 
    pp_div(struct pp_obj* par, any_t par_arg)                     {
        pp_obj*       div    = par       ; if (!div)    return null_t;
        any_t         arg    = par_arg   ; if (!arg)    return null_t;
        pp_obj_trait *trait  = div->trait; if (!trait)  return null_t;
        pp_obj_ops   *pp_ops = trait->ops; if (!pp_ops) return null_t;
        if (!pp_ops->arith)      return null_t;
        if (!pp_ops->arith->div) return null_t;
        return pp_ops->arith->div(div, arg);
}

struct pp_obj* 
    pp_div_eq(struct pp_obj* par, any_t par_arg)                  {
        pp_obj*       div    = par       ; if (!div)    return null_t;
        any_t         arg    = par_arg   ; if (!arg)    return null_t;
        pp_obj_trait *trait  = div->trait; if (!trait)  return null_t;
        pp_obj_ops   *pp_ops = trait->ops; if (!pp_ops) return null_t;
        
        if (!pp_ops->arith)         return null_t;
        if (!pp_ops->arith->div_eq) return null_t;
        pp_ops->arith->div_eq(div, arg);
        return div;
}


struct pp_obj* 
    pp_mod(struct pp_obj* par, any_t par_arg)                     {
        pp_obj*       mod    = par       ; if (!mod)    return null_t;
        any_t         arg    = par_arg   ; if (!arg)    return null_t;
        pp_obj_trait *trait  = mod->trait; if (!trait)  return null_t;
        pp_obj_ops   *pp_ops = trait->ops; if (!pp_ops) return null_t;
        
        if (!pp_ops->arith)      return false_t;
        if (!pp_ops->arith->mod) return false_t;
        return pp_ops->arith->mod(mod, arg);
}

struct pp_obj* 
    pp_mod_eq(struct pp_obj* par, any_t par_arg)                  {
        pp_obj*       mod    = par       ; if (!mod)    return null_t;
        any_t         arg    = par_arg   ; if (!arg)    return null_t;
        pp_obj_trait *trait  = mod->trait; if (!trait)  return null_t;
        pp_obj_ops   *pp_ops = trait->ops; if (!pp_ops) return null_t;
        
        if (!pp_ops->arith)         return false_t;
        if (!pp_ops->arith->mod_eq) return false_t;
        pp_ops->arith->mod_eq(mod, arg);
        return mod;
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