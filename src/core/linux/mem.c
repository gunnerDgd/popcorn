#include <linux/string.h>
#include <linux/module.h>

#include "../mem.h"

void
    po_mem_set
        (void* par, u8_t par_set, u64_t par_size)      {
            if (!par_size) return; u64_t len = par_size;
            if (!par)      return; u8_t* dst = par     ;
            memset(dst, par_set, len);
}

void
    po_mem_copy
        (void* par, void* par_src, u64_t par_size)    {
            if(!par_size) return; u64_t len = par_size;
            if(!par_src)  return; u8_t *src = par_src ;
            if(!par)      return; u8_t *dst = par     ;
            memcpy(dst, src, len);
}

void
    po_mem_move
        (void* par, void* par_src, u64_t par_size)    {
            if(!par_size) return; u64_t len = par_size;
            if(!par_src)  return; u8_t *src = par_src ;
            if(!par)      return; u8_t *dst = par     ;
            memmove(dst, src, len);
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

            if (memcmp(src, cmp, len)) return false_t;
            return true_t;
}

bool_t
    po_mem_gt
        (void* par, void* par_cmp, u64_t par_len, u64_t par_cmp_len)     {
            if (!par_cmp)     return false_t; u8_t *cmp = par_cmp;
            if (!par)         return false_t; u8_t *src = par    ;
            if (!par_cmp_len) return false_t;
            if (!par_len)     return false_t;

            u64_t len = min(par_cmp_len, par_len);
            if (memcmp(src, cmp, len) <= 0) return true_t;
            return false_t;
}

bool_t
    po_mem_lt
        (void* par, void* par_cmp, u64_t par_len, u64_t par_cmp_len)     {
            if (!par_cmp)     return false_t; u8_t *cmp = par_cmp;
            if (!par)         return false_t; u8_t *src = par    ;
            if (!par_cmp_len) return false_t;
            if (!par_len)     return false_t;

            u64_t len = min(par_cmp_len, par_len);
            if (memcmp(src, cmp, len) >= 0) return true_t;
            return false_t;
}

EXPORT_SYMBOL(po_mem_eq);
EXPORT_SYMBOL(po_mem_gt);
EXPORT_SYMBOL(po_mem_lt);

EXPORT_SYMBOL(po_mem_set);
EXPORT_SYMBOL(po_mem_copy);
EXPORT_SYMBOL(po_mem_move);
EXPORT_SYMBOL(po_mem_find);