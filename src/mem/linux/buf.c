#include "../buf.h"
#include <linux/uaccess.h>

u64_t
    po_buf_copy_from
        (po_buf* par, void* par_buf, u64_t par_len, u64_t par_off) {
            if (!par)                            return 0;
            if (trait_of(par) != po_buf_t)       return 0;

            if (!par_buf)                        return 0;
            if (!par_len)                        return 0;
            if (!par_off)                        return 0;
            if (par->size < (par_off + par_len)) return 0;

            return copy_from_user (
                par_buf           ,
                par->buf + par_off,
                par_len
            );
}

u64_t
    po_buf_copy_to
        (po_buf* par, void* par_buf, u64_t par_len, u64_t par_off) {
            if (!par)                            return 0;
            if (trait_of(par) != po_buf_t)       return 0;

            if (!par_buf)                        return 0;
            if (!par_len)                        return 0;
            if (!par_off)                        return 0;
            if (par->size < (par_off + par_len)) return 0;

            return copy_to_user   (
                par->buf + par_off,
                par_buf           ,
                par_len
            );
}

u64_t
    po_buf_size
        (po_buf* par)                              {
            if (!par)                      return 0;
            if (trait_of(par) != po_buf_t) return 0;
            return par->size;
}

u64_t
    po_buf_off
        (po_buf* par)                              {
            if (!par)                      return 0;
            if (trait_of(par) != po_buf_t) return 0;
            return par->off;
}

EXPORT_SYMBOL (po_buf_copy_from);
EXPORT_SYMBOL (po_buf_copy_to)  ;
EXPORT_SYMBOL (po_buf_size)     ;
EXPORT_SYMBOL (po_buf_off)      ;
EXPORT_SYMBOL (po_buf_t)        ;
MODULE_LICENSE("GPL")           ;