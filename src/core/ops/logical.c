#include "logical.h"
#include "../obj.h"

struct po_obj*
    po_log_and(struct po_obj* par, any_t par_arg)                  {
        po_obj*       and   = par       ; if (!and)   return null_t;
        any_t         arg   = par_arg   ; if (!arg)   return null_t;
        po_obj_trait *trait = and->trait; if (!trait) return null_t;
        po_obj_ops   *ops   = trait->ops; if (!ops)   return null_t;

        if (!ops->logical)      return null_t;
        if (!ops->logical->and) return null_t;
        return ops->logical->and(and, arg);
}

struct po_obj*
    po_log_or(struct po_obj* par, any_t par_arg)                   {
        po_obj*       or    = par       ; if (!or)    return null_t;
        any_t         arg   = par_arg   ; if (!arg)   return null_t;
        po_obj_trait *trait = or->trait ; if (!trait) return null_t;
        po_obj_ops   *ops   = trait->ops; if (!ops)   return null_t;

        if (!ops->logical)     return null_t;
        if (!ops->logical->or) return null_t;
        return ops->logical->or(or, arg);
}

struct po_obj*
    po_log_not(struct po_obj* par)                                 {
        po_obj*       not   = par       ; if (!not)   return null_t;
        po_obj_trait *trait = not->trait; if (!trait) return null_t;
        po_obj_ops   *ops   = trait->ops; if (!ops)   return null_t;

        if (!ops->logical)      return null_t;
        if (!ops->logical->not) return null_t;
        return ops->logical->not(not);
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");
#endif