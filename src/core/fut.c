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
        (po_fut* self, u32_t count, va_list arg)                                   {
            po_fut_ops *ops = null_t; if (count > 0) ops = va_arg(arg, po_fut_ops*);
            po_obj     *fut = null_t; if (count > 1) fut = va_arg(arg, po_obj    *);
            if (!ops)       return false_t;
            if (!ops->poll) return false_t;
            if (!ops->ret)  return false_t;
            if (!fut)       return false_t;

            self->stat = po_fut_pend;
            self->fut  = po_ref(fut);
            self->ops  = ops        ;
            return true_t;
}

bool_t
    po_fut_clone
        (po_fut* self, po_fut* clone) {
            return false_t;
}

void   
    po_fut_del
        (po_fut* self)        {
            po_del (self->fut);
}

u64_t  
    po_fut_poll
        (po_fut* self)                                          {
            if (po_trait_of(self) != po_fut_t) return po_fut_err;
            
            self->stat = self->ops->poll(self->fut);
            if (self->stat == po_fut_ready) self->ret = self->ops->ret(self->fut);
            if (self->stat == po_fut_err)   self->ret = self->ops->ret(self->fut);
            return self->stat;
}

void*
    po_fut_ret
        (po_fut* self)                                      {
            if (po_trait_of(self) != po_fut_t) return null_t;
            if (self->stat == po_fut_pend)     return null_t;
            return self->ret;
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(po_fut_poll);
EXPORT_SYMBOL(po_fut_ret);
EXPORT_SYMBOL(po_fut_t);

#endif