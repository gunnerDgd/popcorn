#include "work.h"
#include <linux/sched.h>

po_obj_trait po_work_trait = po_make_trait (
    po_work_new    ,
    po_work_clone  ,
    null_t         ,
    po_work_del    ,
    sizeof(po_work),
    null_t
);

po_obj_trait *po_work_t = &po_work_trait;

static void
    po_work_do
        (struct work_struct* par)                {
            po_work_run* run = (po_work_run*) par;
            run->ret  = run->run(run->arg);
            run->stat = po_fut_ready      ;
}

bool_t
    po_work_new
        (po_work* par_work, u32_t par_count, va_list par)                  {
            void *run = null_t; if (par_count > 0) run = va_arg(par, void*);
            void *arg = null_t; if (par_count > 1) arg = va_arg(par, void*);
            if (!run) return false_t;
            par_work->work.head.func = (work_func_t) po_work_do;
            par_work->work.stat      = po_fut_pend;
            par_work->work.run       = run;
            par_work->work.arg       = arg;

            if (!queue_work(system_long_wq, &par_work->work.head)) return false_t;
            return true_t;
}

bool_t
    po_work_clone
        (po_work* par, po_work* par_clone)  {
            par->work      = par_clone->work;
            par->work.stat = po_fut_pend    ;
            return true_t;
}

void
    po_work_del
        (po_work* par)                                      {
            while (par->work.stat != po_fut_pend) schedule();
}

u64_t
    po_work_poll
        (po_work* par)                                          {
            if (po_trait_of(par) != po_work_t) return po_fut_err;
            return par->work.stat;
}

void*
    po_work_ret
        (po_work* par)                                      {
            if (po_trait_of(par) != po_work_t) return null_t;
            return par->work.ret;
}

po_fut_ops po_work_fut_ops = po_make_fut_ops (
    po_work_poll,
    po_work_ret
);

po_fut*
    po_work_fut
        (po_work* par)                                      {
            if (po_trait_of(par) != po_work_t) return null_t;
            return po_make (po_fut) from                    (
                2               ,
                &po_work_fut_ops,
                par
            );
}

EXPORT_SYMBOL(po_work_fut);
EXPORT_SYMBOL(po_work_t);