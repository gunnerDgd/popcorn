#include "cmp.h"
#include "../obj.h"

po_ord_t
    po_op_ord(struct po_obj* par, any_t par_arg)                {
        po_obj*       cmp    = par       ; if (!cmp)    return 0;
        any_t         arg    = par_arg   ; if (!arg)    return 0;
        po_obj_trait *trait  = cmp->trait; if (!trait)  return 0;
        po_obj_ops   *po_ops = trait->ops; if (!po_ops) return 0;

        if (!po_ops->cmp)      return 0;
        if (!po_ops->cmp->ord) return 0;
        return po_ops->cmp->ord(cmp, arg);
}

bool_t 
    po_op_gt(struct po_obj* par, any_t par_arg)                       {
        po_obj*       cmp    = par       ; if (!cmp)    return false_t;
        any_t         arg    = par_arg   ; if (!arg)    return false_t;
        po_obj_trait *trait  = cmp->trait; if (!trait)  return false_t;
        po_obj_ops   *po_ops = trait->ops; if (!po_ops) return false_t;

        if (!po_ops->cmp)      return false_t;
        if (!po_ops->cmp->ord) return false_t;
        return po_op_ord(cmp, arg) == po_ord_gt;
}

bool_t 
    po_op_gt_eq(struct po_obj* par, any_t par_arg)                    {
        po_obj*       cmp    = par       ; if (!cmp)    return false_t;
        any_t         arg    = par_arg   ; if (!arg)    return false_t;
        po_obj_trait *trait  = cmp->trait; if (!trait)  return false_t;
        po_obj_ops   *po_ops = trait->ops; if (!po_ops) return false_t;

        if (!po_ops->cmp)                     return false_t;
        if (!po_ops->cmp->ord)                return false_t;
        if (po_op_ord(cmp, arg) == po_ord_lt) return false_t;
        return true_t;
}


bool_t 
    po_op_lt(struct po_obj* par, any_t par_arg)                       {
        po_obj*       cmp    = par       ; if (!cmp)    return false_t;
        any_t         arg    = par_arg   ; if (!arg)    return false_t;
        po_obj_trait *trait  = cmp->trait; if (!trait)  return false_t;
        po_obj_ops   *po_ops = trait->ops; if (!po_ops) return false_t;

        if (!po_ops->cmp)      return false_t;
        if (!po_ops->cmp->ord) return false_t;
        return po_op_ord(cmp, arg) == po_ord_lt;
}

bool_t 
    po_op_lt_eq(struct po_obj* par, any_t par_arg)                    {
        po_obj*       cmp    = par       ; if (!cmp)    return false_t;
        any_t         arg    = par_arg   ; if (!arg)    return false_t;
        po_obj_trait *trait  = cmp->trait; if (!trait)  return false_t;
        po_obj_ops   *po_ops = trait->ops; if (!po_ops) return false_t;

        if (!po_ops->cmp)                     return false_t;
        if (!po_ops->cmp->ord)                return false_t;
        if (po_op_ord(cmp, arg) == po_ord_gt) return false_t;
        return true_t;
}

bool_t 
    po_op_eq(struct po_obj* par, any_t par_arg)                       {
        po_obj*       cmp    = par       ; if (!cmp)    return false_t;
        any_t         arg    = par_arg   ; if (!arg)    return false_t;
        po_obj_trait *trait  = cmp->trait; if (!trait)  return false_t;
        po_obj_ops   *po_ops = trait->ops; if (!po_ops) return false_t;

        if (!po_ops->cmp)      return false_t;
        if (!po_ops->cmp->ord) return false_t;
        return po_op_ord(cmp, arg) == po_ord_eq;
}

bool_t 
    po_op_ne(struct po_obj* par, any_t par_arg)                       {
        po_obj*       cmp    = par       ; if (!cmp)    return false_t;
        any_t         arg    = par_arg   ; if (!arg)    return false_t;
        po_obj_trait *trait  = cmp->trait; if (!trait)  return false_t;
        po_obj_ops   *po_ops = trait->ops; if (!po_ops) return false_t;

        if (!po_ops->cmp)      return false_t;
        if (!po_ops->cmp->ord) return false_t;
        return po_op_ord(cmp, arg) != po_ord_eq;
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");
#endif