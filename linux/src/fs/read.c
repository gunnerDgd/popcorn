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
            par_read->read = read;
            par_read->len  = len ;
            par_read->ret  = len ;
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
    po_read_src
        (po_read* par, u8_t* par_buf, u64_t par_len)       {
            if (po_trait_of(par)       != po_read_t) return;
            if (po_trait_of(par->file) != po_file_t) return;

            if (par_len > par->ret) par_len = par->ret;
            if (par->stat != po_fut_pend) return;
            if (!par_buf)                 return;
            if (!par_len)                 return;

            par->ret -= copy_to_user (par->read, par_buf, par_len);
            if (par->ret == par->len)                             {
                par->stat = po_fut_err;
                return;
            }

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
    po_read_poll
        (po_read* par)                                                {
            if (po_trait_of(par)       != po_read_t) return po_fut_err;
            if (po_trait_of(par->file) != po_file_t) return po_fut_err;
            return par->stat;
}

u64_t
    po_read_ret
        (po_read* par)                                                {
            if (po_trait_of(par)       != po_read_t) return po_fut_err;
            if (po_trait_of(par->file) != po_file_t) return po_fut_err;
            return par->ret;
}

po_fut_ops po_read_fut_ops = po_make_fut_ops (
    po_read_poll,
    po_read_ret
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