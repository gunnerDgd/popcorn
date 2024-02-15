#include "sched.h"
#include "task.h"

void*
    po_sched_run
        (po_sched* par)                                          {
            while (po_use_count(par))                            {
                po_task* run = (po_task*) po_mpsc_deq(&par->task);
                if (po_trait_of(run) != po_task_t)               {
                    schedule();
                    continue  ;
                }

                run->ret  = run->run(run->arg);
                run->stat = po_fut_ready      ;
            }

            return null_t;
}

bool_t
    po_sched_new
        (po_sched* par_sched, u32_t par_count, va_list par)                      {
            po_str* name = null_t; if (par_count > 0) name = va_arg(par, po_str*);
            if (po_trait_of(name) != po_str_t) return false_t;

            if (!po_make_at(&par_sched->sched, po_task) from (2, po_sched_run, par_sched)) goto new_err;
            if (!po_make_at(&par_sched->thd  , po_thd)  from (2, &par_sched->sched, name)) goto new_err;
            if (!po_make_at(&par_sched->task , po_mpsc) from (0))                          goto new_err;
            return true_t;
    new_err:
            po_del(&par_sched->task) ;
            po_del(&par_sched->sched);
            po_del(&par_sched->thd)  ;
            return false_t;
}

bool_t
    po_sched_clone
        (po_sched* par, po_sched* par_clone) {
            return false_t;
}

void
    po_sched_del
        (po_sched* par)        {
            po_del(&par->thd)  ;
            po_del(&par->sched);
            po_del(&par->task) ;
}

po_fut*
    po_sched_dispatch
        (po_sched* par, struct po_task* par_task)                  {
            if (po_trait_of (par_task) != po_task_t)  return null_t;
            if (po_trait_of (par)      != po_sched_t) return null_t;
            if (po_use_count(par)      == 0)          return null_t;
            po_mpsc_enq(&par->task, (po_obj*) par_task);
            return po_make (po_fut) from               (
                2           ,
                &po_task_fut,
                par_task
            );
}