#include "mem.h"
#include "macro.h"

po_obj_trait po_mem_trait = po_make_trait (
    po_mem_new    ,
    po_mem_clone  ,
    null_t        ,
    po_mem_del    ,
    sizeof(po_mem),
    null_t
);

po_obj_trait *po_mem_t = &po_mem_trait;

bool_t
    po_mem_new
        (po_mem* par_mem, u32_t par_count, va_list par)                                {
            po_mem_ops *ops = null_t; if (par_count > 0) ops = va_arg(par, po_mem_ops*);
            if (!ops)         return false_t;
            if (!ops->on_acq) return false_t;
            if (!ops->on_rel) return false_t;
            if (!ops->on_new) return false_t;
            if (!ops->on_del) return false_t;

            par_mem->mem = ops->on_new(par_count - 1, par);
            par_mem->ops = ops;

            if (!par_mem->mem) return false_t;
            return true_t;
}

bool_t
    po_mem_clone
        (po_mem* par, po_mem* par_clone) {
            return false_t;
}

void
    po_mem_del
        (po_mem* par)                 {
            par->ops->on_del(par->mem);
}

void*
    po_mem_acq
        (po_mem* par, void* par_hint, u64_t par_len)       {
            if (po_trait_of(par) != po_mem_t) return null_t;
            if (!par_len)                     return null_t;
            return par->ops->on_acq                        (
                par->mem,
                par_hint,
                par_len
            );
}

void
    po_mem_rel
        (po_mem* par, void* par_rel, u64_t par_len) {
            if (po_trait_of(par) != po_mem_t) return;
            if (!par_rel)                     return;
            return par->ops->on_rel                 (
                par->mem,
                par_rel ,
                par_len
            );
}

void
    po_mem_set
        (void* par, u8_t par_set, u64_t par_size)      {
            if (!par_size) return; u64_t len = par_size;
            if (!par)      return; u8_t* dst = par     ;
            while(len--) dst[len] = par_set;
}

void
    po_mem_copy
        (void* par, void* par_src, u64_t par_size)    {
            if(!par_size) return; u64_t len = par_size;
            if(!par_src)  return; u8_t *src = par_src ;
            if(!par)      return; u8_t *dst = par     ;
            while(len--) *dst++ = *src++;
}

void
    po_mem_move
        (void* par, void* par_src, u64_t par_size)    {
            if(!par_size) return; u64_t len = par_size;
            if(!par_src)  return; u8_t *src = par_src ;
            if(!par)      return; u8_t *dst = par     ;
            for (u64_t i = 0 ; i < len ; ++i)         {
                dst[i] = src[i];
                src[i] = 0     ;
            }
}

u64_t
    po_mem_find
        (void* par, void* par_cmp, u64_t par_len, u64_t par_cmp_len)           {
            if (!par_cmp_len)      return -1; u64_t cmp_len = par_cmp_len      ;
            if (!par_len)          return -1; u64_t src_len = par_len          ;
            if (!par_cmp)          return -1; u8_t *cmp     = par_cmp          ;
            if (!par)              return -1; u8_t *src     = par              ;
            if (src_len < cmp_len) return -1; u64_t len     = src_len - cmp_len;
            for(u8_t i = 0 ; i <= len ; ++i)                                   {
                if (po_mem_eq(src + i, cmp, src_len, cmp_len))
                    return i;
            }
            return -1;
}

bool_t
    po_mem_eq
        (void* par, void* par_cmp, u64_t par_len, u64_t par_cmp_len)       {
            if (!par_cmp)               return false_t; u8_t *cmp = par_cmp;
            if (!par)                   return false_t; u8_t *src = par    ;
            if (par_cmp_len != par_len) return false_t; u64_t len = par_len;

            for (u64_t i = 0 ; i < len ; ++i) if (src[i] != cmp[i]) return false_t;
            return true_t;
}

bool_t
    po_mem_gt
        (void* par, void* par_cmp, u64_t par_len, u64_t par_cmp_len)     {
            if (!par_cmp)     return false_t; u8_t *cmp = par_cmp;
            if (!par)         return false_t; u8_t *src = par    ;
            if (!par_cmp_len) return false_t;
            if (!par_len)     return false_t;

            u64_t len = max(par_len, par_cmp_len);
            for (u64_t i = 0 ; i < len ; ++i) if (src[i] < cmp[i]) return false_t;

            if (par_cmp_len == par_len)                         {
                if (src[len - 1] == cmp[len - 1]) return false_t;
                return true_t;
            }

            if (par_cmp_len > par_len) return false_t;
            return true_t;
}

bool_t
    po_mem_lt
        (void* par, void* par_cmp, u64_t par_len, u64_t par_cmp_len)     {
            if (!par_cmp)     return false_t; u8_t *cmp = par_cmp;
            if (!par)         return false_t; u8_t *src = par    ;
            if (!par_cmp_len) return false_t;
            if (!par_len)     return false_t;

            u64_t len = max(par_len, par_cmp_len);
            for (u64_t i = 0 ; i < len ; ++i) if (src[i] < cmp[i]) return false_t;

            if (par_cmp_len == par_len)                         {
                if (src[len - 1] == cmp[len - 1]) return false_t;
                return true_t;
            }

            if (par_cmp_len < par_len) return false_t;
            return true_t;
}