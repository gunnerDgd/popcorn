#include "read.h"
#include "file.h"

po_obj_trait po_read_trait = po_make_trait (
    po_read_new    ,
    po_read_clone  ,
    null_t         ,
    po_read_del    ,
    sizeof(po_read),
    null_t
);

po_obj_trait* po_read_t = &po_read_trait;

bool_t
    po_read_new
        (po_read* par_read, u32_t par_count, va_list par)                          {
            po_file *file = null_t; if (par_count > 0) file = va_arg(par, po_file*);
            u8_t    *read = null_t; if (par_count > 1) read = va_arg(par, u8_t*)   ;
            u64_t    len  = 0     ; if (par_count > 2) len  = va_arg(par, u64_t)   ;
            if (po_trait_of(file) != po_file_t) return false_t;
            if (!read)                          return false_t;
            if (!len)                           return false_t;
            par_read->stat = po_fut_pend;
            par_read->file = file;
            par_read->buf  = read;
            par_read->len  = len ;
            par_read->off  = 0   ;
            return true_t;
}

bool_t
    po_read_clone
        (po_read* par, po_read* par_clone) {
            return false_t;
}

void
    po_read_del
        (po_read* par) {
}

void
    po_read_from
        (po_read* par, u8_t* par_buf, u64_t par_len)       {
            if (po_trait_of(par)       != po_read_t) return;
            if (po_trait_of(par->file) != po_file_t) return;
            if (par->stat != po_fut_pend) return;
            if (!par_buf)                 return;
            if (!par_len)                 return;
            u64_t off = par->off      ;
            u64_t len = par->len - off;
            u8_t* buf = par->buf + off;

            if (par_len > len) par_len = len;
            u64_t ret = copy_to_user        (
                buf    ,
                par_buf,
                len
            );

            par->off += (len - ret);
}

void
    po_read_err
        (po_read* par, u64_t par_err)                      {
            if (po_trait_of(par)       != po_read_t) return;
            if (po_trait_of(par->file) != po_file_t) return;
            if (par->stat != po_fut_pend)            return;
            par->off  = par_err   ;
            par->stat = po_fut_err;
}

void
    po_read_ready
        (po_read* par)                                     {
            if (po_trait_of(par)       != po_read_t) return;
            if (po_trait_of(par->file) != po_file_t) return;
            if (par->stat != po_fut_pend)            return;
            par->stat = po_fut_ready;
}

u64_t
    po_read_len
        (po_read* par)                                       {
            if (po_trait_of(par)       != po_read_t) return 0;
            if (po_trait_of(par->file) != po_file_t) return 0;
            return par->len;
}

u64_t
    po_read_do_poll
        (po_read* par)                                                {
            if (po_trait_of(par)       != po_read_t) return po_fut_err;
            if (po_trait_of(par->file) != po_file_t) return po_fut_err;
            return par->stat;
}

u64_t
    po_read_do_ret
        (po_read* par)                                                {
            if (po_trait_of(par)       != po_read_t) return po_fut_err;
            if (po_trait_of(par->file) != po_file_t) return po_fut_err;
            return par->off;
}

po_fut_ops po_read_fut_ops = po_make_fut_ops (
    po_read_do_poll,
    po_read_do_ret
);

po_fut*
    po_read_fut
        (po_read* par)                                            {
            if (po_trait_of(par)       != po_read_t) return null_t;
            if (po_trait_of(par->file) != po_file_t) return null_t;
            return po_make (po_fut) from                          (
                2               ,
                &po_read_fut_ops,
                par
            );
}

#include <linux/module.h>

MODULE_LICENSE("GPL");
EXPORT_SYMBOL(po_read_from);
EXPORT_SYMBOL(po_read_err);
EXPORT_SYMBOL(po_read_ready);
EXPORT_SYMBOL(po_read_len);
EXPORT_SYMBOL(po_read_fut);
EXPORT_SYMBOL(po_read_t);