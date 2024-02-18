#include "write.h"
#include "dev.h"

bool_t
    po_chr_write_new
        (po_chr_write* par_write, u32_t par_count, va_list par)                            {
            po_chr_dev *dev   = null_t; if (par_count > 0) dev   = va_arg(par, po_chr_dev*);
            u8_t       *write = null_t; if (par_count > 0) write = va_arg(par, u8_t*)      ;
            u64_t       len   = 0     ; if (par_count > 1) len   = va_arg(par, u64_t)      ;
            if (po_trait_of(dev) != po_chr_dev_t) return false_t;
            if (!write)                           return false_t;
            if (!len)                             return false_t;
            par_write->dev   = (po_obj*) po_ref(dev);
            par_write->stat  = po_fut_pend;
            par_write->write = write      ;
            par_write->len   = len        ;
            return true_t;
}

bool_t
    po_chr_write_clone
        (po_chr_write* par, po_chr_write* par_clone) {
            return false_t;
}

void
    po_chr_write_del
        (po_chr_write* par) {
}

u64_t
    po_chr_write_len
        (po_chr_write* par)                                 {
            if (po_trait_of(par) != po_chr_write_t) return 0;
            return par->len;
}

void
    po_chr_write_dest
        (po_chr_write* par, u8_t* par_buf, u64_t par_len) {
            if (po_trait_of(par) != po_chr_write_t) return;
            if (par->stat != po_fut_pend)           return;
            if (!par_buf)                           return;
            if (!par_len)                           return;
            if (par_len >par->len) par_len = par->len;
            par->ret  = copy_from_user               (
                par_buf   ,
                par->write,
                par_len
            );

            if (par->ret == 0)        {
                par->stat = po_fut_err;
                return;
            }

            par->stat = po_fut_ready;
}

u64_t
    po_chr_write_poll
        (po_chr_write* par)                                          {
            if (po_trait_of(par) != po_chr_write_t) return po_fut_err;
            return par->stat;
}

u64_t
    po_chr_write_ret
        (po_chr_write* par)                                          {
            if (po_trait_of(par) != po_chr_write_t) return po_fut_err;
            return par->ret;
}

po_fut_ops po_chr_write_fut_ops = po_make_fut_ops (
        po_chr_write_poll,
        po_chr_write_ret
);

po_fut*
    po_chr_write_fut
        (po_chr_write* par)                                      {
            if (po_trait_of(par) != po_chr_write_t) return null_t;
            return po_make (po_fut) from                         (
                2                    ,
                &po_chr_write_fut_ops,
                par
            );
}