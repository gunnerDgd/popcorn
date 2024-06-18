#include "thd.h"
#include <linux/kthread.h>
#include <linux/ktime.h>

po_obj_trait po_thd_trait = po_make_trait (
    po_thd_new    ,
    po_thd_clone  ,
    null_t        ,
    po_thd_del    ,
    sizeof(po_thd),
    null_t
);

po_obj_trait *po_thd_t = &po_thd_trait;

static int
    do_run
        (any_t arg)                                    {
            if (po_trait_of(arg) != po_thd_t) return -1;
            po_thd *thd = (po_thd*) arg;

            thd->ret  = po_task_run(thd->task);
            thd->stat = po_fut_ready          ;
            return 0;
}

bool_t
    po_thd_new
        (po_thd* self, u32_t count, va_list arg)                               {
            const char *name = null_t; if (count > 0) name = va_arg(arg, any_t);
            po_task    *task = null_t; if (count > 1) task = va_arg(arg, any_t);
            if (po_trait_of(task) != po_task_t) return false_t;

            self->task = (po_task*) po_ref(task);
            self->stat = po_fut_pend;

            self->thd  = kthread_run (do_run, (any_t) self, name);
            if (!self->thd) return false_t;
            return true_t;
}

bool_t
    po_thd_clone
        (po_thd* par, po_thd* par_clone) {
            return false_t;
}

void
    po_thd_del
        (po_thd* self)                                     {
            for ( ; self->stat != po_fut_pend ; schedule());
            po_del(self->task);
}

static u64_t      do_poll(po_thd* self) { if (po_trait_of(self) != po_thd_t) return po_fut_err; return self->stat; }
static any_t      do_ret (po_thd* self) { if (po_trait_of(self) != po_thd_t) return null_t;     return self->ret;  }
static po_fut_ops do_fut = po_make_fut_ops (
    do_poll,
    do_ret
);

po_fut*
    po_thd_fut
        (po_thd* self)                                      {
            if (po_trait_of(self) != po_thd_t) return null_t;
            return po_make (po_fut) from     (
                2      ,
                &do_fut,
                self
            );
}

any_t
    po_await_until
        (po_fut* fut, u32_t until)                         {
            if (po_trait_of(fut) != po_fut_t) return null_t;
            until += jiffies;

            for ( ; time_before(jiffies, until) ; po_yield())
                if (po_fut_poll(fut) != po_fut_pend) {
                    any_t  ret = po_fut_ret(fut);
                    po_del(fut);
                    return ret;
                }

            return null_t;
}

any_t
    po_await
        (po_fut* fut)                                      {
            if (po_trait_of(fut) != po_fut_t) return null_t;

            for ( ; po_fut_poll(fut) != po_fut_pend ; po_yield());
            any_t  ret = po_fut_ret(fut);
            po_del(fut);
            return ret;
}

void
    po_yield(void) {
        schedule();
}

#include <linux/module.h>

MODULE_LICENSE("GPL");
EXPORT_SYMBOL(po_thd_fut);
EXPORT_SYMBOL(po_await_until);
EXPORT_SYMBOL(po_await);
EXPORT_SYMBOL(po_yield);
EXPORT_SYMBOL(po_thd_t);