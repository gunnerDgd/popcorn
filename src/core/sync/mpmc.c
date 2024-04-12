#include "mpmc.h"

#include "../atom.h"
#include "../bit.h"

po_obj_trait po_mpmc_trait = po_make_trait (
    po_mpmc_new    ,
    po_mpmc_clone  ,
    null_t         ,
    po_mpmc_del    ,
    sizeof(po_mpmc),
    null_t
);

po_obj_trait *po_mpmc_t = &po_mpmc_trait;

bool_t
    po_mpmc_new
        (po_mpmc* par_spsc, u32_t par_count, va_list par)           {
            po_mem_set(par_spsc->mpmc, 0x00, sizeof(par_spsc->mpmc));
            par_spsc->enq = 0;
            par_spsc->deq = 0;
            return true_t;
}

bool_t
    po_mpmc_clone
        (po_mpmc* par, po_mpmc* par_clone) {
            return false_t;
}

void
    po_mpmc_del
        (po_mpmc* par)                       {
            while (par->enq != par->deq)     {
                po_del  (par->mpmc[par->deq]);
                par->deq += 1       ;
                par->deq &= mask(10);
            }
}

bool_t
    po_mpmc_enq_try
        (po_mpmc* par, po_obj* par_enq)                          {
            if (po_trait_of(par)     != po_mpmc_t) return false_t;
            if (po_trait_of(par_enq) == null_t)    return false_t;
            u64_t  pos = par->enq            ;
            u64_t  enq = (pos + 1) & mask(10);
            po_ref(par_enq);

            if    (enq == par->deq)                                   return false_t;
            if    (po_lock_cas_ptr(&par->enq, pos, enq) != pos)       return false_t;
            while (po_lock_cas_ptr(&par->mpmc[pos], null_t, par_enq));
            return true_t;
            
}

void
    po_mpmc_enq
        (po_mpmc* par, po_obj* par_enq)                  {
            if (po_trait_of(par)     != po_mpmc_t) return;
            if (po_trait_of(par_enq) == null_t)    return;
            while (!po_mpmc_enq_try(par, par_enq));
}

po_obj*
    po_mpmc_deq_try
        (po_mpmc* par)                                      {
            if (po_trait_of(par) != po_mpmc_t) return null_t;
            u64_t   pos = par->deq            ;
            u64_t   deq = (pos + 1) & mask(10);
            po_obj *ret = par->mpmc[pos]      ;

            if    (pos == par->enq)                                      return null_t;
            if    (!ret)                                                 return null_t;
            if    (po_lock_cas_ptr(&par->deq, pos, deq)          != pos) return null_t;
            while (po_lock_cas_ptr(&par->mpmc[pos], ret, null_t) != ret) ret = par->mpmc[pos];
            po_del(ret);
            return ret;
}

po_obj*
    po_mpmc_deq
        (po_mpmc* par)                                                   {
            if (po_trait_of(par) != po_mpmc_t) return null_t; po_obj* ret;
            while (!(ret = po_mpmc_deq_try(par)));
            return   ret;
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");
#endif