#include "task.h"

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
        (po_task* self, u32_t count, va_list par)                      {
            any_t fun = null_t; if (count > 0) fun = va_arg(par, any_t);
            any_t arg = null_t; if (count > 1) arg = va_arg(par, any_t);

            if (!fun) return false_t;
            self->fun = fun;
            self->arg = arg;
            return true_t;
}

bool_t
    po_task_clone
        (po_task* self, po_task* clone) {
            self->fun = clone->fun;
            self->arg = clone->arg;
            return true_t;
}

void   po_task_del  (po_task* self) {}

any_t
    po_task_run
        (po_task* self)                                      {
            if (po_trait_of(self) != po_task_t) return null_t;
            return self->fun(self->arg);
}