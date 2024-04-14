#include "seq.h"

po_obj_trait po_seq_trait = po_make_trait (
    po_seq_new    ,
    po_seq_clone  ,
    null_t        ,
    po_seq_del    ,
    sizeof(po_seq),
    null_t
);

po_obj_trait *po_seq_t = &po_seq_trait;

bool_t
    po_seq_new
        (po_seq* par_seq, u32_t par_count, va_list par)                      {
            u64_t   len = 16ull ; if (par_count > 0) len = va_arg(par, u64_t);
            po_mem* mem = null_t; if (par_count > 1) mem = va_arg(par, void*);
            if (po_trait_of(mem) != po_mem_t) mem = po_get_mem();
            if (po_trait_of(mem) != po_mem_t) return false_t ;
            if (len < 16) len = 16;

            par_seq->ptr   = po_mem_acq (mem, null_t, len);
            par_seq->begin = 0  ;
            par_seq->end   = 0  ;
            par_seq->mem   = mem;
            par_seq->len   = len;
            return true_t;
}

bool_t
    po_seq_clone
        (po_seq* par, po_seq* par_clone) {
            par->begin = par_clone->begin;
            par->end   = par_clone->end  ;
            par->len   = par_clone->len  ;
            par->mem   = par_clone->mem  ;

            par->ptr = po_mem_acq(par->mem, null_t, par->len); if (!par->ptr) return false_t;
            po_mem_copy(par->ptr, par_clone->ptr, par->len);
            return true_t;
}

void
    po_seq_del
        (po_seq* par)                               {
            po_mem_rel(par->mem, par->ptr, par->len);
}

void
    po_seq_prep_front
        (po_seq* par, u64_t par_len)                {
            if (po_trait_of(par) != po_seq_t) return;
            if (!par_len)                     return;

            u8_t *ptr = po_mem_acq(par->mem, null_t, par->len + par_len);
            u8_t *dst = ptr      + par->begin + par_len;
            u8_t *src = par->ptr + par->begin;
            u64_t len = po_seq_len(par);

            po_mem_copy(dst, src, len)               ;
            po_mem_rel (par->mem, par->ptr, par->len);
            par->begin += par_len;
            par->end   += par_len;
            par->len   += len;
            par->ptr    = ptr;
}

void
    po_seq_prep_back
        (po_seq* par, u64_t par_len)                {
            if (po_trait_of(par) != po_seq_t) return;
            if (!par_len)                     return;

            u8_t *ptr = po_mem_acq(par->mem, null_t, par->len + par_len);
            u8_t *dst = ptr      + par->begin;
            u8_t *src = par->ptr + par->begin;
            u64_t len = po_seq_len(par);

            po_mem_copy(dst, src, len);
            po_mem_rel (par->mem, par->ptr, par->len);
            par->len += par_len;
            par->ptr  = ptr    ;
}

void
    po_seq_prep
        (po_seq* par, u64_t par_off, u64_t par_len) {
            if (po_trait_of(par) != po_seq_t) return;
            if (!par_len)                     return;

            if (par_off >= po_seq_len(par)) { po_seq_prep_back (par, par_len); return; }
            if (par_off == 0)               { po_seq_prep_front(par, par_len); return; }
            u8_t *ptr = po_mem_acq(par->mem, null_t, par_len + par->len);
            u8_t *dst = ptr      + par->begin;
            u8_t *src = par->ptr + par->begin;
            u64_t len = par_off;

            po_mem_copy(dst, src, len);
            len  = po_seq_len(par) - par_off;
            dst += (par_off + par_len);
            src += (par_off);

            po_mem_copy(dst, src, len)               ;
            po_mem_rel (par->mem, par->ptr, par->len);
            par->end += par_len;
            par->ptr  = ptr    ;
            par->len += par_len;
}

u64_t
    po_seq_free_front
        (po_seq* par)                                 {
            if (po_trait_of(par) != po_seq_t) return 0;
            return par->begin;
}

u64_t
    po_seq_free_back
        (po_seq* par)                                 {
            if (po_trait_of(par) != po_seq_t) return 0;
            return par->len - par->end;
}

bool_t
    po_seq_empty
        (po_seq* par)                                      {
            if (po_trait_of(par) != po_seq_t) return true_t;
            return par->begin == par->end;
}

u64_t
    po_seq_len
        (po_seq* par)                                 {
            if (po_trait_of(par) != po_seq_t) return 0;
            return par->end - par->begin;
}

void*
    po_seq_ptr
        (po_seq* par)                                      {
            if (po_trait_of(par) != po_seq_t) return null_t;
            return par->ptr + par->begin;
}

void
    po_seq_push_front
        (po_seq* par, void* par_src, u64_t par_len) {
            if (po_trait_of(par) != po_seq_t) return;
            if (!par_src)                     return;
            if (!par_len)                     return;

            if (po_seq_free_front(par) < par_len) po_seq_prep_front(par, par_len);
            par->begin -= par_len;

            u8_t *dst = par->ptr + par->begin;
            u8_t *src = par_src;
            u64_t len = par_len;

            po_mem_copy(dst, src, len);
}

void
    po_seq_push_back
        (po_seq* par, void* par_src, u64_t par_len) {
            if (po_trait_of(par) != po_seq_t) return;
            if (!par_src)                     return;
            if (!par_len)                     return;

            if (po_seq_free_back(par) < par_len) po_seq_prep_back(par, par_len);
            u8_t *dst = par->ptr + par->end;
            u8_t *src = par_src;
            u64_t len = par_len;

            po_mem_copy(dst, src, len);
            par->end += par_len;
}

void
    po_seq_push
        (po_seq* par, void* par_src, u64_t par_len, u64_t par_off) {
            if (po_trait_of(par) != po_seq_t) return;
            if (!par_src)                     return;
            if (!par_len)                     return;

            if (par_off > po_seq_len(par)) { po_seq_push_back (par, par_src, par_len); return; }
            if (par_off == 0)              { po_seq_push_front(par, par_src, par_len); return; }
            po_seq_prep(par, par_off, par_len);

            u8_t *dst = par->ptr + par->begin + par_off;
            u8_t *src = par_src;
            u64_t len = par_len;

            po_mem_copy(dst, src, len);
}

void
    po_seq_pop_front
        (po_seq* par, u64_t par_len)                {
            if (po_trait_of(par) != po_seq_t) return;
            if (!par_len)                     return;
            if (par->begin < par_len)               {
                par->begin = 0;
                return;
            }

            par->begin -= par_len;
            po_mem_set(par->ptr + par->begin, 0x00, par_len);
}

void
    po_seq_pop_back
        (po_seq* par, u64_t par_len)                {
            if (po_trait_of(par) != po_seq_t) return;
            if (!par_len)                     return;
            if (par_len >= po_seq_len(par))                             {
                po_mem_set(par->ptr + par->begin, 0x00, po_seq_len(par));
                par->end = par->begin;
            }

            par->end -= par_len;
            po_mem_set(par->ptr + par->end, 0x00, par_len);
}

void
    po_seq_pop
        (po_seq* par, u64_t par_off, u64_t par_len) {
            if (po_trait_of(par) != po_seq_t) return;
            if (!par_len)                     return;

            if (par_off > par->end) { po_seq_pop_back (par, par_len); return; }
            if (par_off == 0)       { po_seq_pop_front(par, par_len); return; }
            u8_t *dst = par->ptr + par_off;
            u8_t *src = dst      + par_len;
            u64_t len = par_len;

            if (len > (par->end - par_off)) len = (par->end - par_off);
            po_mem_copy(dst, src, len);

            par->end -= par_len;
            po_mem_set(par->ptr + par->end, 0x00, par_len);
}

#ifdef PRESET_LINUX
#include <linux/module.h>

EXPORT_SYMBOL(po_seq_push_front);
EXPORT_SYMBOL(po_seq_push_back);
EXPORT_SYMBOL(po_seq_push);
EXPORT_SYMBOL(po_seq_pop_front);
EXPORT_SYMBOL(po_seq_pop_back);
EXPORT_SYMBOL(po_seq_pop);
EXPORT_SYMBOL(po_seq_free_front);
EXPORT_SYMBOL(po_seq_free_back);
EXPORT_SYMBOL(po_seq_prep_front);
EXPORT_SYMBOL(po_seq_prep_back);
EXPORT_SYMBOL(po_seq_t);
#endif