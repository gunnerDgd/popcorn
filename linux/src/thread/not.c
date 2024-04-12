#include "not.h"

po_obj_trait po_not_trait = po_make_trait (
    po_not_new    ,
    po_not_clone  ,
    null_t        ,
    po_not_del    ,
    sizeof(po_not),
    null_t
);

po_obj_trait *po_not_t = &po_not_trait;

bool_t po_not_new  (po_not* par_event, u32_t par_count, va_list par) { return true_t ; }
bool_t po_not_clone(po_not* par, po_not* par_clone)                  { return false_t; }
void   po_not_del  (po_not* par)                                     {}

bool_t
    po_not_wait_until
        (po_not* par, u64_t par_time)                       {
            if (po_trait_of(par) != po_not_t) return false_t;
            u64_t ret = wait_event_interruptible_timeout    (
                par->not,
                0       ,
                par_time
            );

            if (ret == 0) return false_t;
            return true_t;
}

void
    po_not_wait
        (po_not* par)                               {
            if (po_trait_of(par) != po_not_t) return;
            wait_event_interruptible(par->not, 0);
}

void
    po_not_wake
        (po_not* par)                               {
            if (po_trait_of(par) != po_not_t) return;
            wake_up_interruptible(&par->not);
}