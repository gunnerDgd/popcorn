#include "spmc.h"

#include "../atom.h"
#include "../bit.h"

po_obj_trait po_spmc_trait = po_make_trait (
    po_spmc_new    ,
    po_spmc_clone  ,
    null_t         ,
    po_spmc_del    ,
    sizeof(po_spmc),
    null_t
);

po_obj_trait *po_spmc_t = &po_spmc_trait;

bool_t
    po_spmc_new
        (po_spmc* par_spsc, u32_t par_count, va_list par)           {
            po_mem_set(par_spsc->spmc, 0x00, sizeof(par_spsc->spmc));
            par_spsc->enq = 0;
            par_spsc->deq = 0;
            return true_t;
}

bool_t
    po_spmc_clone
        (po_spmc* par, po_spmc* par_clone) {
            return false_t;
}

void
    po_spmc_del
        (po_spmc* par)                      {
            while (par->enq != par->deq)    {
                po_del (par->spmc[par->deq]);
                par->deq += 1       ;
                par->deq &= mask(10);
            }
}

bool_t
    po_spmc_enq_try
        (po_spmc* par, po_obj* par_enq)                          {
            if (po_trait_of(par)     != po_spmc_t) return false_t;
            if (po_trait_of(par_enq) == null_t)    return false_t;
            u64_t pos = par->enq            ;
            u64_t enq = (pos + 1) & mask(10);

            if    (enq == par->deq) return false_t;
            while (par->spmc[pos]);

            par->spmc[pos] = po_ref(par_enq);
            par->enq       = pos            ;
            return true_t;
            
}

void
    po_spmc_enq
        (po_spmc* par, po_obj* par_enq)                  {
            if (po_trait_of(par)     != po_spmc_t) return;
            if (po_trait_of(par_enq) == null_t)    return;
            while (!po_spmc_enq_try(par, par_enq));
}

po_obj*
    po_spmc_deq_try
        (po_spmc* par)                                      {
            if (po_trait_of(par) != po_spmc_t) return null_t;
            u64_t   pos = par->deq            ;
            u64_t   deq = (pos + 1) & mask(10);
            po_obj *ret = 0                   ;

            if    (pos == par->enq)                             return null_t;
            if    (po_lock_cas_ptr(&par->deq, pos, deq) != pos) return null_t;
            while (!par->spmc[pos]);

            ret = par->spmc[pos];
            par->spmc[pos]   = 0;
            po_del(ret);
            return ret;
}

po_obj*
    po_spmc_deq
        (po_spmc* par)                                                   {
            if (po_trait_of(par) != po_spmc_t) return null_t; po_obj* ret;
            while (!(ret = po_spmc_deq_try(par)));
            return   ret;
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");
#endif