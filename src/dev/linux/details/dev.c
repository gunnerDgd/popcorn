#include "dev.h"
#include "dev_type.h"

#include <linux/sched.h>

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
        (po_dev* par_dev, u32_t par_count, va_list par)                                  {
            const char  *name = NULL; if (par_count > 0) name = va_arg(par, const char*) ;
            po_dev_type *type = NULL; if (par_count > 1) type = va_arg(par, po_dev_type*);
            po_dev_ops  *ops  = NULL; if (par_count > 2) ops  = va_arg(par, po_dev_ops *);
            po_obj      *dev  = NULL; if (par_count > 3) dev  = va_arg(par, po_obj     *);

            if (!name)                           return false_t;
            if (!type)                           return false_t;
            if (!ops)                            return false_t;

            if (trait_of(type) != po_dev_type_t) return false_t;
            if (type->num == 64 KB)              return false_t;

            if (!ops->on_new)                    return false_t;
            if (!ops->on_ref)                    return false_t;
            if (!ops->on_del)                    return false_t;

            if (!ops->on_read)                   return false_t;
            if (!ops->on_write)                  return false_t;
            if (!ops->on_control)                return false_t;

            par_dev->idx     = type->num++            ;
            par_dev->id      = type->id + par_dev->idx;

            par_dev->hnd     = po_list_push_back(&type->use, (po_obj*)par_dev);
            par_dev->dev_hnd = device_create    (
                type->cls    ,
                NULL         ,
                par_dev->id  ,
                par_dev      ,
                name
            );

            if (!make_at(&par_dev->name, &po_str_t) from (0)) goto new_failed;
            if (!par_dev->dev_hnd)                            goto new_failed;
            if (!par_dev->hnd)                                goto new_failed;

            po_str_push_back_cstr(&par_dev->name, name, strlen(name));
            par_dev->type = type     ;
            par_dev->dev  = ref(dev) ;
            par_dev->ops  = ops      ;

            type->dev[par_dev->idx] = par_dev;
            return true_t;
    new_failed:
            po_list_pop(&type   ->use, par_dev->hnd);
            del        (&par_dev->name)             ;
            return false_t;
}

bool_t
    po_dev_clone
        (po_dev* par, po_dev* par_clone) {
            return false_t;
}

void
    po_dev_del
        (po_dev* par)                              {
            po_dev_wait   (par, po_dev_free)       ;
            device_destroy(par->type->cls, par->id);

            par->type->dev[par->idx] = NULL;
            del (par->dev) ;
}

po_str*
    po_dev_name
        (po_dev* par)                                 {
            if (!par)                      return NULL;
            if (trait_of(par) != po_dev_t) return NULL;

            return &par->name;
}
void
    po_dev_wait
        (po_dev* par, u64_t par_state)           {
            if (!par)                      return;
            if (trait_of(par) != po_dev_t) return;
            if (par_state > po_dev_busy)   return;

            while (par->state != par_state) schedule();
}