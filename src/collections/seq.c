#include "seq.h"

static bool_t
    do_new
        (pp_seq* par_seq, u32_t par_count, va_list par)                      {
            u64_t   len = 16ull ; if (par_count > 0) len = va_arg(par, u64_t);
            pp_mem* mem = null_t; if (par_count > 1) mem = va_arg(par, void*);
            if (pp_trait_of(mem) != pp_mem_t) mem = pp_get_mem();
            if (pp_trait_of(mem) != pp_mem_t) return false_t ;
            if (len < 16) len = 16;

            par_seq->ptr   = pp_mem_use (mem, null_t, len);
            par_seq->begin = 0  ;
            par_seq->end   = 0  ;
            par_seq->mem   = mem;
            par_seq->len   = len;
            return true_t;
}

static bool_t
    do_clone
        (pp_seq* par, pp_seq* par_clone) {
            par->begin = par_clone->begin;
            par->end   = par_clone->end  ;
            par->len   = par_clone->len  ;
            par->mem   = par_clone->mem  ;

            par->ptr = pp_mem_use(par->mem, null_t, par->len); if (!par->ptr) return false_t;
            pp_mem_copy(par->ptr, par_clone->ptr, par->len);
            return true_t;
}

static void
    do_del
        (pp_seq* par)   {
            pp_mem_free (
                par->mem,
                par->ptr,
                par->len
            );
}

static pp_obj_trait
    do_obj = pp_make_trait (
        do_new        ,
        do_clone      ,
        null_t        ,
        do_del        ,
        sizeof(pp_seq),
        null_t
);

pp_obj_trait *pp_seq_t = &do_obj;

void
    pp_seq_prep_front
        (pp_seq* par, u64_t par_len)                {
            if (pp_trait_of(par) != pp_seq_t) return;
            if (!par_len)                     return;

            u8_t *ptr = pp_mem_use(par->mem, null_t, par->len + par_len);
            u8_t *dst = ptr      + par->begin + par_len;
            u8_t *src = par->ptr + par->begin;
            u64_t len = pp_seq_len(par);
            pp_mem_copy (dst, src, len);

            pp_mem_free(par->mem, par->ptr, par->len);
            par->begin += par_len;
            par->end   += par_len;
            par->len   += len;
            par->ptr    = ptr;
}

void
    pp_seq_prep_back
        (pp_seq* par, u64_t par_len)                {
            if (pp_trait_of(par) != pp_seq_t) return;
            if (!par_len)                     return;

            u8_t *ptr = pp_mem_use(par->mem, null_t, par->len + par_len);
            u8_t *dst = ptr      + par->begin;
            u8_t *src = par->ptr + par->begin;
            u64_t len = pp_seq_len(par);
            pp_mem_copy(dst, src, len);

            pp_mem_free(par->mem, par->ptr, par->len);
            par->len += par_len;
            par->ptr  = ptr    ;
}

void
    pp_seq_prep
        (pp_seq* par, u64_t par_off, u64_t par_len) {
            if (pp_trait_of(par) != pp_seq_t) return;
            if (!par_len)                     return;

            if (par_off >= pp_seq_len(par)) { pp_seq_prep_back (par, par_len); return; }
            if (par_off == 0)               { pp_seq_prep_front(par, par_len); return; }
            u8_t *ptr = pp_mem_use(par->mem, null_t, par_len + par->len);
            u8_t *dst = ptr      + par->begin;
            u8_t *src = par->ptr + par->begin;
            u64_t len = par_off;

            pp_mem_copy(dst, src, len);
            len  = pp_seq_len(par) - par_off;
            dst += (par_off + par_len);
            src += (par_off);

            pp_mem_copy(dst, src, len)               ;
            pp_mem_free(par->mem, par->ptr, par->len);
            par->end += par_len;
            par->ptr  = ptr    ;
            par->len += par_len;
}

u64_t
    pp_seq_free_front
        (pp_seq* par)                                 {
            if (pp_trait_of(par) != pp_seq_t) return 0;
            return par->begin;
}

u64_t
    pp_seq_free_back
        (pp_seq* par)                                 {
            if (pp_trait_of(par) != pp_seq_t) return 0;
            return par->len - par->end;
}

bool_t
    pp_seq_empty
        (pp_seq* par)                                      {
            if (pp_trait_of(par) != pp_seq_t) return true_t;
            return par->begin == par->end;
}

u64_t
    pp_seq_len
        (pp_seq* par)                                 {
            if (pp_trait_of(par) != pp_seq_t) return 0;
            return par->end - par->begin;
}

void*
    pp_seq_ptr
        (pp_seq* par)                                      {
            if (pp_trait_of(par) != pp_seq_t) return null_t;
            return par->ptr + par->begin;
}

void
    pp_seq_push_front
        (pp_seq* par, void* par_src, u64_t par_len) {
            if (pp_trait_of(par) != pp_seq_t) return;
            if (!par_src)                     return;
            if (!par_len)                     return;

            if (pp_seq_free_front(par) < par_len) pp_seq_prep_front(par, par_len);
            par->begin -= par_len;

            u8_t *dst = par->ptr + par->begin;
            u8_t *src = par_src;
            u64_t len = par_len;

            pp_mem_copy(dst, src, len);
}

void
    pp_seq_push_back
        (pp_seq* par, void* par_src, u64_t par_len) {
            if (pp_trait_of(par) != pp_seq_t) return;
            if (!par_src)                     return;
            if (!par_len)                     return;

            if (pp_seq_free_back(par) < par_len) pp_seq_prep_back(par, par_len);
            u8_t *dst = par->ptr + par->end;
            u8_t *src = par_src;
            u64_t len = par_len;

            pp_mem_copy(dst, src, len);
            par->end += par_len;
}

void
    pp_seq_push
        (pp_seq* par, void* par_src, u64_t par_len, u64_t par_off) {
            if (pp_trait_of(par) != pp_seq_t) return;
            if (!par_src)                     return;
            if (!par_len)                     return;

            if (par_off > pp_seq_len(par)) { pp_seq_push_back (par, par_src, par_len); return; }
            if (par_off == 0)              { pp_seq_push_front(par, par_src, par_len); return; }
            pp_seq_prep(par, par_off, par_len);

            u8_t *dst = par->ptr + par->begin + par_off;
            u8_t *src = par_src;
            u64_t len = par_len;

            pp_mem_copy(dst, src, len);
}

void
    pp_seq_pop_front
        (pp_seq* par, u64_t par_len)                {
            if (pp_trait_of(par) != pp_seq_t) return;
            if (!par_len)                     return;
            if (par->begin < par_len)               {
                par->begin = 0;
                return;
            }

            par->begin -= par_len;
            pp_mem_set(par->ptr + par->begin, 0x00, par_len);
}

void
    pp_seq_pop_back
        (pp_seq* par, u64_t par_len)                {
            if (pp_trait_of(par) != pp_seq_t) return;
            if (!par_len)                     return;
            if (par_len >= pp_seq_len(par))                             {
                pp_mem_set(par->ptr + par->begin, 0x00, pp_seq_len(par));
                par->end = par->begin;
            }

            par->end -= par_len;
            pp_mem_set(par->ptr + par->end, 0x00, par_len);
}

void
    pp_seq_pop
        (pp_seq* par, u64_t par_off, u64_t par_len) {
            if (pp_trait_of(par) != pp_seq_t) return;
            if (!par_len)                     return;

            if (par_off > par->end) { pp_seq_pop_back (par, par_len); return; }
            if (par_off == 0)       { pp_seq_pop_front(par, par_len); return; }
            u8_t *dst = par->ptr + par_off;
            u8_t *src = dst      + par_len;
            u64_t len = par_len;

            if (len > (par->end - par_off)) len = (par->end - par_off);
            pp_mem_copy(dst, src, len);

            par->end -= par_len;
            pp_mem_set(par->ptr + par->end, 0x00, par_len);
}

#ifdef PRESET_LINUX
#include <linux/module.h>

EXPORT_SYMBOL(pp_seq_push_front);
EXPORT_SYMBOL(pp_seq_push_back);
EXPORT_SYMBOL(pp_seq_push);
EXPORT_SYMBOL(pp_seq_pop_front);
EXPORT_SYMBOL(pp_seq_pop_back);
EXPORT_SYMBOL(pp_seq_pop);
EXPORT_SYMBOL(pp_seq_free_front);
EXPORT_SYMBOL(pp_seq_free_back);
EXPORT_SYMBOL(pp_seq_prep_front);
EXPORT_SYMBOL(pp_seq_prep_back);
EXPORT_SYMBOL(pp_seq_t);
#endif