#include "mem.h"

po_mem* mem;

po_mem*
    po_get_mem(void) {
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
            if (!par)         return 0;
            if (!par->on_new) return 0;

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

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");
#endif