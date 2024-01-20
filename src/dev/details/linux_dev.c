#include "linux_dev.h"
#include "linux_chr.h"

#include <linux/sched.h>
#include <asm-generic/cmpxchg-local.h>

po_obj_trait po_dev_trait            = {
    .on_new   = as_new  (&po_dev_new)  ,
    .on_clone = as_clone(&po_dev_clone),
    .on_ref   = 0                      ,
    .on_del   = as_del  (&po_dev_del)  ,
    .size     = sizeof(po_dev)
};

po_obj_trait *po_dev_t = &po_dev_trait;

bool_t
    po_dev_new
        (po_dev* par_dev, u32_t par_count, va_list par)                                 {
            const char  *name = NULL; if (par_count > 0) name = va_arg(par, const char*);
            po_ns       *ns   = NULL; if (par_count > 1) ns   = va_arg(par, po_ns     *);
            po_dev_ops  *ops  = NULL; if (par_count > 2) ops  = va_arg(par, po_dev_ops*);
            po_obj      *dev  = NULL; if (par_count > 3) dev  = va_arg(par, po_obj    *);

            if (!name)                                        return false_t;
            if (!ns)                                          return false_t;
            if (trait_of(ns) != po_ns_t)                      return false_t;

            if (!ops)                                         return false_t;
            if (!ops->on_new)                                 return false_t;
            if (!ops->on_open)                                return false_t;
            if (!ops->on_close)                               return false_t;
            if (!ops->on_del)                                 return false_t;

            if (!ops->on_read)                                return false_t;
            if (!ops->on_write)                               return false_t;
            if (!ops->on_control)                             return false_t;
            if (!make_at (&par_dev->name, po_str_t) from (0)) return false_t;

            po_str_push_back_cstr(&par_dev->name, name, strlen(name));
            par_dev->ns  = (po_ns*) ref(ns);
            par_dev->obj = ref(dev)        ;
            par_dev->ops = ops             ;
            par_dev->id  = -1              ;
            return true_t;
    new_failed:
}

bool_t
    po_dev_clone
        (po_dev* par, po_dev* par_clone) {
            return false_t;
}

void
    po_dev_del
        (po_dev* par)      {
            del(&par->name);
            del(par->obj)  ;
            del(par->ns)   ;
}

#ifdef PO_PRESET_LINUX
#include <linux/module.h>

MODULE_LICENSE("GPL");
#endif