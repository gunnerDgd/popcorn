#include "task.h"

static bool_t
    do_new
        (pp_task* self, u32_t count, va_list par)                      {
            any_t fun = null_t; if (count > 0) fun = va_arg(par, any_t);
            any_t arg = null_t; if (count > 1) arg = va_arg(par, any_t);

            if (!fun) return false_t;
            self->fun = fun;
            self->arg = arg;
            return true_t;
}

static bool_t
    do_clone
        (pp_task* self, pp_task* clone) {
            self->fun = clone->fun;
            self->arg = clone->arg;
            return true_t;
}

static void
    do_del
        (pp_task* self) {
}

static pp_obj_trait
    do_obj = pp_make_trait (
        do_new         ,
        do_clone       ,
        null_t         ,
        do_del         ,
        sizeof(pp_task),
        null_t
);

pp_obj_trait *pp_task_t = &do_obj;

any_t
    pp_task_run
        (pp_task* self)                                      {
            if (pp_trait_of(self) != pp_task_t) return null_t;
            return self->fun(self->arg);
}

#ifdef PRESET_LINUX
#include <linux/module.h>

MODULE_LICENSE("GPL");
EXPORT_SYMBOL(pp_task_t);
EXPORT_SYMBOL(pp_task_run);
#endif