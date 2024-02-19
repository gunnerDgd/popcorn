#include "read.h"
#include "dev.h"

po_obj_trait po_chr_read_trait = po_make_trait (
    po_chr_read_new    ,
    po_chr_read_clone  ,
    null_t             ,
    po_chr_read_del    ,
    sizeof(po_chr_read),
    null_t
);

po_obj_trait* po_chr_read_t = &po_chr_read_trait;

bool_t
    po_chr_read_new
        (po_chr_read* par_read, u32_t par_count, va_list par)                            {
            po_chr_dev *dev  = null_t; if (par_count > 0) dev  = va_arg(par, po_chr_dev*);
            u8_t       *read = null_t; if (par_count > 1) read = va_arg(par, u8_t*)      ;
            u64_t       len  = 0     ; if (par_count > 2) len  = va_arg(par, u64_t)      ;
            if (po_trait_of(dev) != po_chr_dev_t) return false_t;
            if (!read)                            return false_t;
            if (!len)                             return false_t;
            par_read->dev  = (po_chr_dev*) po_ref(dev);
            par_read->stat = po_fut_pend;
            par_read->read = read       ;
            par_read->len  = len        ;
            return true_t;
}

bool_t
    po_chr_read_clone
        (po_chr_read* par, po_chr_read* par_clone) {
            return false_t;
}

void
    po_chr_read_del
        (po_chr_read* par)   {
            po_del (par->dev);
}


void
    po_chr_read_src
        (po_chr_read* par, u8_t* par_buf, u64_t par_len) {
            if (po_trait_of(par) != po_chr_read_t) return;
            if (par->stat != po_fut_pend)          return;
            if (!par_buf)                          return;
            if (!par_len)                          return;
            if (par_len >par->len) par_len = par->len;
            par->ret = copy_to_user                  (
                par->read,
                par_buf  ,
                par->ret
            );

            if (par->ret == 0)        {
                par->stat = po_fut_err;
                return;
            }

            par->stat = po_fut_ready;
}

u64_t
    po_chr_read_poll
        (po_chr_read* par)                                          {
            if (po_trait_of(par) != po_chr_read_t) return po_fut_err;
            return par->stat;
}

u64_t
    po_chr_read_ret
        (po_chr_read* par)                                          {
            if (po_trait_of(par) != po_chr_read_t) return po_fut_err;
            return par->ret;
}

po_fut_ops po_chr_read_fut_ops = po_make_fut_ops (
    po_chr_read_poll,
    po_chr_read_ret
);

po_fut*
    po_chr_read_fut
        (po_chr_read* par)                                      {
            if (po_trait_of(par) != po_chr_read_t) return null_t;
            return po_make (po_fut) from                        (
                2                   ,
                &po_chr_read_fut_ops,
                par
            );
}