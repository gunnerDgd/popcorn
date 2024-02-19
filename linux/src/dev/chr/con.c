#include "con.h"
#include "dev.h"

po_obj_trait po_chr_con_trait = po_make_trait (
    po_chr_con_new    ,
    po_chr_con_clone  ,
    null_t            ,
    po_chr_con_del    ,
    sizeof(po_chr_con),
    null_t
);

po_obj_trait* po_chr_con_t = &po_chr_con_trait;

bool_t
    po_chr_con_new
        (po_chr_con* par_con, u32_t par_count, va_list par)                            {
            po_chr_dev *dev = null_t; if (par_count > 0) dev = va_arg(par, po_chr_dev*);
            u64_t       cmd = 0     ; if (par_count > 1) cmd = va_arg(par, u64_t)      ;
            u64_t       arg = 0     ; if (par_count > 2) arg = va_arg(par, u64_t)      ;
            if (po_trait_of(dev) != po_chr_dev_t) return false_t;

            par_con->dev = (po_chr_dev*) po_ref(dev);
            par_con->cmd = cmd;
            par_con->arg = arg;
            return true_t;
}

bool_t
    po_chr_con_clone
        (po_chr_con* par, po_chr_con* par_clone) {
            return false_t;
}

void
    po_chr_con_del
        (po_chr_con* par)    {
            po_del (par->dev);
}

void
    po_chr_con_ret
        (po_chr_con* par, u64_t par_ret)                     {
            if (po_trait_of(par)      != po_chr_con_t) return;
            if (po_trait_of(par->dev) != po_chr_dev_t) return;
            if (par->stat             != po_fut_pend)  return;
            par->ret  = par_ret     ;
            par->stat = po_fut_ready;
}

u64_t
    po_chr_con_arg
        (po_chr_con* par)                                  {
            if (po_trait_of(par) != po_chr_con_t) return -1;
            if (po_trait_of(par) != po_chr_dev_t) return -1;
            if (par->stat != po_fut_pend)         return -1;
            return par->arg;
}

u64_t
    po_chr_con_cmd
        (po_chr_con* par)                                  {
            if (po_trait_of(par) != po_chr_con_t) return -1;
            if (po_trait_of(par) != po_chr_dev_t) return -1;
            if (par->stat != po_fut_pend)         return -1;
            return par->cmd;
}

u64_t
    po_chr_con_do_poll
        (po_chr_con* par)                                          {
            if (po_trait_of(par) != po_chr_con_t) return po_fut_err;
            if (po_trait_of(par) != po_chr_dev_t) return po_fut_err;
            return par->stat;
}

u64_t
    po_chr_con_do_ret
        (po_chr_con* par)                                          {
            if (po_trait_of(par) != po_chr_con_t) return po_fut_err;
            if (po_trait_of(par) != po_chr_dev_t) return po_fut_err;
            return par->ret;
}

po_fut_ops po_chr_con_fut_ops = po_make_fut_ops (
    po_chr_con_do_poll,
    po_chr_con_do_ret
);

po_fut*
    po_chr_con_fut
        (po_chr_con* par)                                      {
            if (po_trait_of(par) != po_chr_con_t) return null_t;
            if (po_trait_of(par) != po_chr_dev_t) return null_t;
            return po_make (po_fut) from                       (
                2                  ,
                &po_chr_con_fut_ops,
                par
            );
}