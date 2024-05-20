#include "control.h"
#include "file.h"

po_obj_trait po_control_trait = po_make_trait (
    po_control_new    ,
    po_control_clone  ,
    null_t            ,
    po_control_del    ,
    sizeof(po_control),
    null_t
);

po_obj_trait* po_control_t = &po_control_trait;

bool_t
    po_control_new
        (po_control* par_con, u32_t par_count, va_list par)                        {
            po_file *file = null_t; if (par_count > 0) file = va_arg(par, po_file*);
            u64_t    code = 0     ; if (par_count > 1) code = va_arg(par, u64_t)   ;
            any_t    arg  = 0     ; if (par_count > 2) arg  = va_arg(par, any_t)   ;
            if (po_trait_of(file) != po_file_t) return false_t;

            par_con->stat = po_fut_pend;
            par_con->file = file;
            par_con->code = code;
            par_con->arg  = arg ;
            return true_t;
}

bool_t
    po_control_clone
        (po_control* par, po_control* par_clone) {
            return false_t;
}

void
    po_control_del
        (po_control* par)    {
}

void
    po_control_ready
        (po_control* par, u64_t par_ret)                      {
            if (po_trait_of(par)       != po_control_t) return;
            if (po_trait_of(par->file) != po_file_t)    return;
            if (par->stat              != po_fut_pend)  return;
            par->ret  = par_ret     ;
            par->stat = po_fut_ready;
}

any_t
    po_control_arg
        (po_control* par)                                            {
            if (po_trait_of(par)       != po_control_t) return null_t;
            if (po_trait_of(par->file) != po_file_t)    return null_t;
            if (par->stat != po_fut_pend)               return null_t;
            return par->arg;
}

u64_t
    po_control_code
        (po_control* par)                                        {
            if (po_trait_of(par)       != po_control_t) return -1;
            if (po_trait_of(par->file) != po_file_t)    return -1;
            if (par->stat != po_fut_pend)               return -1;
            return par->code;
}

u64_t
    po_control_do_poll
        (po_control* par)                                                {
            if (po_trait_of(par)       != po_control_t) return po_fut_err;
            if (po_trait_of(par->file) != po_file_t)    return po_fut_err;
            return par->stat;
}

u64_t
    po_control_do_ret
        (po_control* par)                                          {
            if (po_trait_of(par)       != po_control_t) return 0ull;
            if (po_trait_of(par->file) != po_file_t)    return 0ull;
            return par->ret;
}

po_fut_ops po_control_fut_ops = po_make_fut_ops (
    po_control_do_poll,
    po_control_do_ret
);

po_fut*
    po_control_fut
        (po_control* par)                                            {
            if (po_trait_of(par)       != po_control_t) return null_t;
            if (po_trait_of(par->file) != po_file_t)    return null_t;
            return po_make (po_fut) from                             (
                2                  ,
                &po_control_fut_ops,
                par
            );
}

#include <linux/module.h>
EXPORT_SYMBOL(po_control_ready);
EXPORT_SYMBOL(po_control_code);
EXPORT_SYMBOL(po_control_arg);
EXPORT_SYMBOL(po_control_fut);
EXPORT_SYMBOL(po_control_t);