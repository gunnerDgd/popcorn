#include "../this.h"

#include <linux/module.h>
#include <linux/ktime.h>
#include <linux/sched.h>

void
    po_yield
        (void)        {
            schedule();
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

            for ( ; po_fut_poll(fut) == po_fut_pend ; po_yield());
            any_t  ret = po_fut_ret(fut);
            po_del(fut);
            return ret;
}

MODULE_LICENSE("GPL");

EXPORT_SYMBOL(po_yield)      ;
EXPORT_SYMBOL(po_await_until);
EXPORT_SYMBOL(po_await)      ;