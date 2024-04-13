#include "fut.h"

po_obj_trait po_fut_trait = po_make_trait (
    po_fut_new    ,
    po_fut_clone  ,
    null_t        ,
    po_fut_del    ,
    sizeof(po_fut),
    null_t
);

po_obj_trait* po_fut_t = &po_fut_trait;

bool_t
    po_fut_new
        (po_fut* par_fut, u32_t par_count, va_list par)                                {
            po_fut_ops *ops = null_t; if (par_count > 0) ops = va_arg(par, po_fut_ops*);
            po_obj     *fut = null_t; if (par_count > 1) fut = va_arg(par, po_obj    *);
            if (!ops)       return false_t;
            if (!ops->poll) return false_t;
            if (!ops->ret)  return false_t;
            if (!fut)       return false_t;

            par_fut->stat = po_fut_pend;
            par_fut->fut  = po_ref(fut);
            par_fut->ops  = ops        ;
            return true_t;
}

bool_t
    po_fut_clone
        (po_fut* par, po_fut* par_clone) {
            return false_t;
}

void   
    po_fut_del
        (po_fut* par)        {
            po_del (par->fut);
}

u64_t  
    po_fut_poll
        (po_fut* par)                                          {
            if (!par)                         return po_fut_err;
            if (po_trait_of(par) != po_fut_t) return po_fut_err;
            
            par->stat = par->ops->poll(par->fut);
            if (par->stat == po_fut_ready) par->ret = par->ops->ret(par->fut);
            if (par->stat == po_fut_err)   par->ret = par->ops->ret(par->fut);
            return par->stat;
}

void*
    po_fut_ret
        (po_fut* par)                                      {
            if (!par)                         return null_t;
            if (po_trait_of(par) != po_fut_t) return null_t;
            if (par->stat == po_fut_pend)     return null_t;
            return par->ret;
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(po_fut_poll);
EXPORT_SYMBOL(po_fut_ret);
EXPORT_SYMBOL(po_fut_t);

#endif