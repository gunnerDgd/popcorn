#include "mem.h"
#include <linux/slab.h>

void*   mem_slab_new(po_mem* par, u64_t par_size) { return kzalloc(par_size, GFP_KERNEL); }
void    mem_slab_del(po_mem* par, void* par_mem)  { kfree(par_mem); }
po_mem  mem_slab        = {
    .on_new = mem_slab_new,
    .on_del = mem_slab_del
};

po_mem* mem = &mem_slab;
po_mem*
    po_get_mem
        (void)        {
            return mem;
}

po_mem* 
    po_set_mem
        (po_mem* par)                   {
            po_mem* ret = mem; mem = par;
            return  ret;
}

void* 
    po_mem_new    
        (po_mem* par, u64_t par_size)  {
            if (!par)         par = mem;
            if (!par)         return 0 ;
            if (!par->on_new) return 0 ;

            return par->on_new(par, par_size);
}

void  
    po_mem_del
        (po_mem* par, void* par_del)   {
            if (!par)         par = mem;
            if (!par)         return;
            if (!par->on_del) return;

            par->on_del(par, par_del);
}

void   po_mem_set (void* par, u8_t  par_set, u64_t par_size) { memset (par, par_set, par_size); }
void   po_mem_copy(void* par, void* par_src, u64_t par_size) { memcpy (par, par_src, par_size); }
void   po_mem_move(void* par, void* par_src, u64_t par_size) { memmove(par, par_src, par_size); }

bool_t po_mem_eq  (void* par, void* par_cmp, u64_t par_size) { return (memcmp(par, par_cmp, par_size) == 0); }
bool_t po_mem_gt  (void* par, void* par_cmp, u64_t par_size) { return (memcmp(par, par_cmp, par_size) >  0); }
bool_t po_mem_lt  (void* par, void* par_cmp, u64_t par_size) { return (memcmp(par, par_cmp, par_size) <  0); }

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



#ifdef PO_PRESET_LINUX
#include <linux/module.h>

MODULE_LICENSE("GPL");
#endif