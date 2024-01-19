#include "mem.h"

po_mem* global_po_mem;

po_mem* 
    po_get_mem
        (void)                  {
            return global_po_mem;
}

po_mem* 
    po_set_mem
        (po_mem* par)                                 {
            po_mem* ret = global_po_mem; global_po_mem = par;
            return   ret;
}

void* 
    po_mem_new    
        (po_mem* par, u64_t par_size)            {
            if (!par)         par = global_po_mem;
            if (!par)         return 0;
            if (!par->on_new) return 0;

            return par->on_new(par, par_size);
}

void  
    po_mem_del
        (po_mem* par, void* par_del)             {
            if (!par)         par = global_po_mem;
            if (!par)         return;
            if (!par->on_del) return;

            par->on_del(par, par_del);
}

void
    po_mem_set
        (void* par, u8_t par_set, u64_t par_size) {
            if (!par_size) return;
            while(par_size--)
                ((u8_t*)par)[par_size] = par_set;
}

void
    po_mem_copy
        (void* par, void* par_src, u64_t par_size) {
            if(!par_size) return;
            if(!par)      return;
            if(!par_src)  return;

            u8_t* dst = par, * src = par_src;
            while(par_size--)
                *dst++ = *src++;
}

void
    po_mem_move
        (void* par, void* par_src, u64_t par_size) {
            if (!par_size) return;
            if (!par)      return;
            if (!par_src)  return;

            u8_t* dst = par, * src = par_src;
            for(u8_t i = 0 ; i < par_size ; ++i) {
                dst[i] = src[i];
                src[i] =      0;
            }
}

u64_t  
    po_mem_find
        (void* par, void* par_cmp, u64_t par_len, u64_t par_cmp_len) {
            if (!par)                  return -1;
            if (!par_cmp)              return -1;
            if (!par_len)              return -1;
            if (!par_cmp_len)          return -1;
            if (par_len < par_cmp_len) return -1;

            u8_t *src = par, *src_cmp = par_cmp;
            for(u8_t i = 0 ; i <= (par_len - par_cmp_len) ; ++i)
                if (po_mem_eq(src + i, src_cmp, par_cmp_len))
                    return i;

            return -1;
}

bool_t 
    po_mem_eq
        (void* par, void* par_cmp, u64_t par_size) {
            if (!par)      return false_t;
            if (!par_cmp)  return false_t;
            if (!par_size) return false_t;

            for (u64_t i = 0 ; i < par_size ; ++i)
                if (((u8_t*)par)[i] != ((u8_t*)par_cmp)[i])
                    return false_t;

            return true_t;
}

bool_t 
    po_mem_gt
        (void* par, void* par_cmp, u64_t par_size) {
            if (!par)      return false_t;
            if (!par_cmp)  return false_t;
            if (!par_size) return false_t;

            for (u64_t i = 0 ; i < par_size ; ++i)
                if (((u8_t*)par)[i] < ((u8_t*)par_cmp)[i])
                    return false_t;

            return ((u8_t*)par)[par_size - 1] > ((u8_t*)par_cmp)[par_size - 1];
}

bool_t 
    po_mem_lt
        (void* par, void* par_cmp, u64_t par_size) {
            if (!par)      return false_t;
            if (!par_cmp)  return false_t;
            if (!par_size) return false_t;

            for (u64_t i = 0 ; i < par_size ; ++i)
                if (((u8_t*)par)[i] != ((u8_t*)par_cmp)[i])
                    return false_t;

            return true_t;
}

#ifdef PO_PRESET_LINUX
#include <linux/module.h>

MODULE_LICENSE("GPL");
#endif