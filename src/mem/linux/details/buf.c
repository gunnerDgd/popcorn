#include "buf.h"

po_obj_trait po_buf_trait            = {
    .on_new   = as_new  (&po_buf_new)  ,
    .on_clone = as_clone(&po_buf_clone),
    .on_ref   = 0                      ,
    .on_del   = as_del  (&po_buf_del)  ,
    .size     = sizeof(po_buf)
};

po_obj_trait *po_buf_t = &po_buf_trait;

bool_t
    po_buf_new
        (po_buf* par_buf, u32_t par_count, va_list par)                            {
            __user void* buf  = NULL ; if (par_count > 0) buf  = va_arg(par, void*);
            u64_t        size = 0    ; if (par_count > 1) size = va_arg(par, u64_t);
            u64_t        off  = 0    ; if (par_count > 2) off  = va_arg(par, u64_t);

            if (!buf)  return false_t;
            if (!size) return false_t;
            if (!off)  return false_t;

            par_buf->buf  = buf ;
            par_buf->size = size;
            par_buf->off  = off ;
            return true_t;
}

bool_t
    po_buf_clone
        (po_buf* par, po_buf* par_clone) {
            return false_t;
}

void
    po_buf_del
        (po_buf* par) {
            return;
}