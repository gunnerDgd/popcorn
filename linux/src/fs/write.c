#include "write.h"
#include "file.h"

po_obj_trait po_write_trait = po_make_trait (
    po_write_new    ,
    po_write_clone  ,
    null_t          ,
    po_write_del    ,
    sizeof(po_write),
    null_t
);

po_obj_trait *po_write_t = &po_write_trait;

bool_t
    po_write_new
        (po_write* par_write, u32_t par_count, va_list par)                          {
            po_file *file  = null_t; if (par_count > 0) file  = va_arg(par, po_file*);
            u8_t    *write = null_t; if (par_count > 0) write = va_arg(par, u8_t*)   ;
            u64_t    len   = 0     ; if (par_count > 1) len   = va_arg(par, u64_t)   ;
            if (po_trait_of(file) != po_file_t) return false_t;
            if (!write)                         return false_t;
            if (!len)                           return false_t;
            par_write->stat = po_fut_pend;
            par_write->file = file ;
            par_write->buf  = write;
            par_write->len  = len  ;
            par_write->off  = 0    ;
            return true_t;
}

bool_t
    po_write_clone
        (po_write* par, po_write* par_clone) {
            return false_t;
}

void
    po_write_del
        (po_write* par) {
}

u8_t*
    po_write_buf
        (po_write* par)                                            {
            if (po_trait_of(par)       != po_write_t) return null_t;
            if (po_trait_of(par->file) != po_file_t)  return null_t;
            return par->buf;
}

void
    po_write_ready
        (po_write* par)                                     {
            if (po_trait_of(par)       != po_write_t) return;
            if (po_trait_of(par->file) != po_file_t)  return;
            if (par->stat != po_fut_pend)             return;
            par->stat = po_fut_ready;
}

void
    po_write_err
        (po_write* par, u64_t par_err)                      {
            if (po_trait_of(par)       != po_write_t) return;
            if (po_trait_of(par->file) != po_file_t)  return;
            par->off  = par_err   ;
            par->stat = po_fut_err;
}

u64_t
    po_write_len
        (po_write* par)                                       {
            if (po_trait_of(par)       != po_write_t) return 0;
            if (po_trait_of(par->file) != po_file_t)  return 0;
            return par->len;
}

void
    po_write_to
        (po_write* par, u8_t* par_buf, u64_t par_len)       {
            if (po_trait_of(par)       != po_write_t) return;
            if (po_trait_of(par->file) != po_file_t)  return;
            if (par->stat != po_fut_pend) return;
            if (!par_buf)                 return;
            if (!par_len)                 return;
            u64_t off = par->off      ;
            u64_t len = par->len - off;
            u8_t* buf = par->buf + off;

            if (par_len > len) par_len = len;
            u64_t ret = copy_from_user      (
                par_buf,
                buf    ,
                len
            );

            par->off += (len - ret);
}

u64_t
    po_write_do_poll
        (po_write* par)                                                {
            if (po_trait_of(par)       != po_write_t) return po_fut_err;
            if (po_trait_of(par->file) != po_file_t)  return po_fut_err;
            return par->stat;
}

u64_t
    po_write_do_ret
        (po_write* par)                                                {
            if (po_trait_of(par)       != po_write_t) return po_fut_err;
            if (po_trait_of(par->file) != po_file_t)  return po_fut_err;
            return par->off;
}

po_fut_ops po_write_fut_ops = po_make_fut_ops (
        po_write_do_poll,
        po_write_do_ret
);

po_fut*
    po_write_fut
        (po_write* par)                                            {
            if (po_trait_of(par)       != po_write_t) return null_t;
            if (po_trait_of(par->file) != po_file_t)  return null_t;
            return po_make (po_fut) from                           (
                2                ,
                &po_write_fut_ops,
                par
            );
}

#include <linux/module.h>
MODULE_LICENSE("GPL");
EXPORT_SYMBOL(po_write_to);
EXPORT_SYMBOL(po_write_len);
EXPORT_SYMBOL(po_write_ready);
EXPORT_SYMBOL(po_write_err);
EXPORT_SYMBOL(po_write_buf);
EXPORT_SYMBOL(po_write_fut);
EXPORT_SYMBOL(po_write_t);