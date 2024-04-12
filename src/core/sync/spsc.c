#include "spsc.h"

#include "../atom.h"
#include "../bit.h"

po_obj_trait po_spsc_trait = po_make_trait (
    po_spsc_new    ,
    po_spsc_clone  ,
    null_t         ,
    po_spsc_del    ,
    sizeof(po_spsc),
    null_t
);

po_obj_trait *po_spsc_t = &po_spsc_trait;

bool_t
    po_spsc_new
        (po_spsc* par_spsc, u32_t par_count, va_list par)           {
            po_mem_set(par_spsc->spsc, 0x00, sizeof(par_spsc->spsc));
            par_spsc->enq = 0;
            par_spsc->deq = 0;
            return true_t;
}

bool_t
    po_spsc_clone
        (po_spsc* par, po_spsc* par_clone) {
            return false_t;
}

void
    po_spsc_del
        (po_spsc* par)                           {
            while (par->enq != par->deq)         {
                po_obj *ret = par->spsc[par->deq];
                po_del (ret);

                par->deq += 1       ;
                par->deq &= mask(10);
            }
}

bool_t
    po_spsc_enq_try
        (po_spsc* par, po_obj* par_enq)                      {
            if (po_trait_of(par) != po_spsc_t) return false_t;
            u64_t pos = par->enq            ;
            u64_t enq = (pos + 1) & mask(10);

            if (enq == par->deq) return false_t;
            par->spsc[pos] = po_ref(par_enq);
            par->enq       = enq            ;
            return true_t;
            
}

void
    po_spsc_enq
        (po_spsc* par, po_obj* par_enq)              {
            if (po_trait_of(par) != po_spsc_t) return;
            while (!po_spsc_enq_try(par, par_enq));
}

po_obj*
    po_spsc_deq_try
        (po_spsc* par)                                      {
            if (po_trait_of(par) != po_spsc_t) return null_t;
            u64_t   pos = par->deq            ;
            u64_t   deq = (pos + 1) & mask(10);
            po_obj *ret = par->spsc[pos]      ;

            if (pos == par->enq) return null_t;
            par->deq = deq;
            po_del(ret);
            return ret ;
}

po_obj*
    po_spsc_deq
        (po_spsc* par)                                                   {
            if (po_trait_of(par) != po_spsc_t) return null_t; po_obj* ret;
            while (!(ret = po_spsc_deq_try(par)));
            return   ret;
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");
#endif