#include "mpsc.h"

#include "../atom.h"
#include "../bit.h"

po_obj_trait po_mpsc_trait = po_make_trait (
    po_mpsc_new    ,
    po_mpsc_clone  ,
    null_t         ,
    po_mpsc_del    ,
    sizeof(po_mpsc),
    null_t
);

po_obj_trait *po_mpsc_t = &po_mpsc_trait;

bool_t
    po_mpsc_new
        (po_mpsc* par_spsc, u32_t par_count, va_list par)           {
            po_mem_set(par_spsc->mpsc, 0x00, sizeof(par_spsc->mpsc));
            par_spsc->enq = 0;
            par_spsc->deq = 0;
            return true_t;
}

bool_t
    po_mpsc_clone
        (po_mpsc* par, po_mpsc* par_clone) {
            return false_t;
}

void
    po_mpsc_del
        (po_mpsc* par)                     {
            while (par->enq != par->deq)   {
                po_del(par->mpsc[par->deq]);
                par->deq += 1       ;
                par->deq &= mask(10);
            }
}

bool_t
    po_mpsc_enq_try
        (po_mpsc* par, po_obj* par_enq)                          {
            if (po_trait_of(par)     != po_mpsc_t) return false_t;
            if (po_trait_of(par_enq) == null_t)    return false_t;
            u64_t pos = par->enq            ;
            u64_t enq = (pos + 1) & mask(10);

            if    (enq == par->deq)                             return false_t;
            if    (po_lock_cas_ptr(&par->enq, pos, enq) != pos) return false_t;
            while (par->mpsc[pos]);

            par->mpsc[pos] = po_ref(par_enq);
            return true_t;
            
}

void
    po_mpsc_enq
        (po_mpsc* par, po_obj* par_enq)                  {
            if (po_trait_of(par)     != po_mpsc_t) return;
            if (po_trait_of(par_enq) == null_t)    return;
            while (!po_mpsc_enq_try(par, par_enq));
}

po_obj*
    po_mpsc_deq_try
        (po_mpsc* par)                                      {
            if (po_trait_of(par) != po_mpsc_t) return null_t;
            u64_t   pos = par->deq            ;
            u64_t   deq = (pos + 1) & mask(10);
            po_obj *ret = 0                   ;

            if    (pos == par->enq) return null_t;
            while (!par->mpsc[pos]);

            ret            = par->mpsc[pos];
            par->mpsc[pos] = 0  ;
            par->deq       = deq;
            po_del(ret);
            return ret ;
}

po_obj*
    po_mpsc_deq
        (po_mpsc* par)                                                   {
            if (po_trait_of(par) != po_mpsc_t) return null_t; po_obj* ret;
            while (!(ret = po_mpsc_deq_try(par)));
            return   ret;
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");
#endif