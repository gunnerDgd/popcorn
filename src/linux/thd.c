#include "thd.h"
#include "task.h"

int
    po_thd_run
        (any_t par)                                                                          {
            if (po_trait_of(par)       != po_thd_t)  return -1; po_thd  *thd  = (po_thd*) par;
            if (po_trait_of(thd->task) != po_task_t) return -1; po_task *task = thd->task;
            task->ret  = task->run(task->arg);
            task->stat = po_fut_ready        ;
            return 0;
}

bool_t
    po_thd_new
        (po_thd* par_thd, u32_t par_count, va_list par)                            {
            po_task *task = null_t; if (par_count > 0) task = va_arg(par, po_task*);
            po_str  *name = null_t; if (par_count > 1) name = va_arg(par, po_str*) ;
            if (po_trait_of(task) != po_task_t) return false_t;
            if (po_trait_of(name) != po_str_t)  return false_t;
            if (task->sup)                      return false_t;
            task->sup     = po_ref(par_thd);
            par_thd->task = po_ref(par_thd);
            par_thd->thd  = kthread_run    (
                po_thd_run        ,
                (any_t) par_thd   ,
                po_str_as_raw(name)
            );

            return true_t;
    new_err:
            po_del(task->sup)    ;
            po_del(par_thd->task);
            return false_t;
}

bool_t
    po_thd_clone
        (po_thd* par, po_thd* par_clone) {
            return false_t;
}

void
    po_thd_del
        (po_thd* par)                                        {
            if   (po_trait_of(par->task) != po_task_t) return;
            if   (!par->thd)                           return;
            while(par->task->stat != po_fut_pend) schedule();
}

po_fut*
    po_thd_fut
        (po_thd* par)                                             {
            if (po_trait_of(par)       != po_thd_t)  return null_t;
            if (po_trait_of(par->task) != po_task_t) return null_t;
            return po_make (po_fut) from                          (
                2           ,
                &po_task_fut,
                par->task
            );
}