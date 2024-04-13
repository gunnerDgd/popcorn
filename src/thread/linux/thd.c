#include "thd.h"

po_obj_trait po_thd_trait = po_make_trait (
    po_thd_new    ,
    po_thd_clone  ,
    null_t        ,
    po_thd_del    ,
    sizeof(po_thd),
    null_t
);

po_obj_trait *po_thd_t = &po_thd_trait;

int
    po_thd_run
        (any_t par)                                                                  {
            if (po_trait_of(par) != po_thd_t)  return -1; po_thd *thd = (po_thd*) par;
            thd->ret  = thd->func(thd->arg);
            thd->stat = po_fut_ready       ;
            return 0;
}

bool_t
    po_thd_new
        (po_thd* par_thd, u32_t par_count, va_list par)                          {
            void   *func = null_t; if (par_count > 0) func = va_arg(par, void*)  ;
            void   *arg  = null_t; if (par_count > 1) arg  = va_arg(par, void*)  ;
            po_str *name = null_t; if (par_count > 2) name = va_arg(par, po_str*);
            if (po_trait_of(name) != po_str_t) return false_t;
            if (!func)                         return false_t;

            if (!po_make_at (&par_thd->name, po_str) from (0)) return false_t;
            po_str_push_back(&par_thd->name, name);

            par_thd->stat = po_fut_pend;
            par_thd->func = func;
            par_thd->arg  = arg ;

            par_thd->thd  = kthread_run (po_thd_run, (any_t) par_thd, po_str_ptr(&par_thd->name));
            if (!par_thd->thd)        {
                po_del(&par_thd->name);
                return false_t;
            }
            return true_t;
}

bool_t
    po_thd_clone
        (po_thd* par, po_thd* par_clone) {
            return false_t;
}

void
    po_thd_del
        (po_thd* par)              {
            if   (!par->thd) return;
            while(par->stat != po_fut_pend) {
                schedule();
            }

            po_del(&par->name);
}

u64_t
    po_thd_do_poll
        (po_thd* par)                                          {
            if (po_trait_of(par) != po_thd_t) return po_fut_err;
            return par->stat;
}

any_t
    po_thd_do_ret
        (po_thd* par)                                      {
            if (po_trait_of(par) != po_thd_t) return null_t;
            return par->ret;
}

po_fut_ops po_thd_do = po_make_fut_ops (
    po_thd_do_poll,
    po_thd_do_ret
);

po_fut*
    po_thd_fut
        (po_thd* par)                                       {
            if (po_trait_of(par) != po_thd_t)  return null_t;
            return po_make (po_fut) from                    (
                2         ,
                &po_thd_do,
                par
            );
}

#include <linux/module.h>

MODULE_LICENSE("GPL");
EXPORT_SYMBOL(po_thd_fut);
EXPORT_SYMBOL(po_thd_t);