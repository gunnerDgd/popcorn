#include "task.h"
#include "sched.h"

#include <linux/sched.h>

po_obj_trait po_task_trait = po_make_trait (
    po_task_new    ,
    po_task_clone  ,
    null_t         ,
    po_task_del    ,
    sizeof(po_task),
    null_t
);

po_obj_trait *po_task_t = &po_task_trait;

bool_t
    po_task_new
        (po_task* par_task, u32_t par_count, va_list par)                  {
            void* run = null_t; if (par_count > 0) run = va_arg(par, void*);
            void* arg = null_t; if (par_count > 1) run = va_arg(par, void*);
            if (!run) return false_t;

            par_task->stat = po_fut_pend;
            par_task->run  = run;
            par_task->arg  = arg;
            return true_t;
}

bool_t
    po_task_clone
        (po_task* par, po_task* par_clone) {
            par->stat = po_fut_pend   ;
            par->run  = par_clone->run;
            par->arg  = par_clone->arg;
            par->sup  = null_t        ;
            return true_t;
}

void
    po_task_del
        (po_task* par)                                 {
            while (par->stat != po_fut_pend) schedule();
            po_del(par->sup);
}

u64_t
    po_task_poll
        (po_task* par)                                          {
            if (po_trait_of(par) != po_task_t) return po_fut_err;
            return par->stat;
}

void*
    po_task_ret
        (po_task* par)                                      {
            if (po_trait_of(par) != po_task_t) return null_t;
            if (par->stat == po_fut_pend)      return null_t;
            return par->ret;
}

po_fut_ops po_task_fut = po_make_fut_ops (
        po_task_poll,
        po_task_ret
);