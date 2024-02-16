#include "read.h"

bool_t
    po_read_new
        (po_read* par_read, u32_t par_count, va_list par)                    {
            u8_t* dest = null_t; if (par_count > 0) dest = va_arg(par, u8_t*);
            u64_t len  = 0     ; if (par_count > 1) len  = va_arg(par, u64_t);
            if (!dest) return false_t;
            if (!len)  return false_t;

            par_read->stat = po_fut_pend;
            par_read->dest = dest       ;
            par_read->len  = len        ;
            return true_t;
}

bool_t
    po_read_clone
        (po_read* par, po_read* par_clone) {
            return false_t;
}

void
    po_read_del
        (po_read* par)                                 {
            copy_to_user(par->dest, par->src, par->ret);
}

u64_t
    po_read_len
        (po_read* par)                                 {
            if (po_trait_of(par) != po_read_t) return 0;
            return par->len;
}

void
    po_read_src
        (po_read* par, u8_t* par_buf, u64_t par_len) {
            if (po_trait_of(par) != po_read_t) return;
            if (!par_buf)                      return;
            if (!par_len)                      return;
            if (par_len >par->len) par_len = par->len;
            par->stat = po_fut_ready;
            par->ret  = par_len     ;
            par->src  = par_buf     ;
}

u64_t
    po_read_poll
        (po_read* par)                                          {
            if (po_trait_of(par) != po_read_t) return po_fut_err;
            return par->stat;
}

u64_t
    po_read_ret
        (po_read* par)                                          {
            if (po_trait_of(par) != po_read_t) return po_fut_err;
            return par->ret;
}

po_fut_ops po_read_fut_ops = po_make_fut_ops (
    po_read_poll,
    po_read_ret
);

po_fut*
    po_read_fut
        (po_read* par)                                      {
            if (po_trait_of(par) != po_read_t) return null_t;
            return po_make (po_fut) from                    (
                2               ,
                &po_read_fut_ops,
                par
            );
}