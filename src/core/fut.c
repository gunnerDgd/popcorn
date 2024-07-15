#include "fut.h"

static bool_t
    do_new
        (pp_fut* self, u32_t count, va_list arg)                                   {
            pp_fut_ops *ops = null_t; if (count > 0) ops = va_arg(arg, pp_fut_ops*);
            pp_obj     *fut = null_t; if (count > 1) fut = va_arg(arg, pp_obj    *);
            if (!ops)       return false_t;
            if (!ops->poll) return false_t;
            if (!ops->ret)  return false_t;
            if (!fut)       return false_t;

            self->stat = pp_fut_pend;
            self->fut  = pp_ref(fut);
            self->ops  = ops        ;
            return true_t;
}

static bool_t
    do_clone
        (pp_fut* self, pp_fut* clone) {
            return false_t;
}

static void
    do_del
        (pp_fut* self)        {
            pp_del (self->fut);
}

static pp_obj_trait
    do_obj = pp_make_trait (
        do_new        ,
        do_clone      ,
        null_t        ,
        do_del        ,
        sizeof(pp_fut),
        null_t
);

pp_obj_trait* pp_fut_t = &do_obj;

u64_t  
    pp_fut_poll
        (pp_fut* self)                                          {
            if (pp_trait_of(self) != pp_fut_t) return pp_fut_err;
            
            self->stat = self->ops->poll(self->fut);
            if (self->stat == pp_fut_ready) self->ret = self->ops->ret(self->fut);
            if (self->stat == pp_fut_err)   self->ret = self->ops->ret(self->fut);
            return self->stat;
}

void*
    pp_fut_ret
        (pp_fut* self)                                      {
            if (pp_trait_of(self) != pp_fut_t) return null_t;
            if (self->stat == pp_fut_pend)     return null_t;
            return self->ret;
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(pp_fut_poll);
EXPORT_SYMBOL(pp_fut_ret);
EXPORT_SYMBOL(pp_fut_t);

#endif