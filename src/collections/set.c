#include "set.h"

po_obj_trait po_set_root_trait = po_make_trait (
    po_set_root_new    ,
    po_set_root_clone  ,
    null_t             ,
    po_set_root_del    ,
    sizeof(po_set_root),
    null_t
);

po_obj_trait *po_set_root_t = &po_set_root_trait;

bool_t
    po_set_root_new
        (po_set_root* par_root, u32_t par_count, va_list par)       {
            po_mem_set(par_root->node, 0x00, sizeof(par_root->node));
            po_mem_set(par_root->sub , 0x00, sizeof(par_root->sub)) ;
            par_root->num  =  0;
            par_root->free =  0;
            par_root->use  = -1;
            return true_t;
}

bool_t
    po_set_root_clone
        (po_set_root* par, po_set_root* par_clone) {
            return false_t;
}

void
    po_set_root_del
        (po_set_root* par)                                                  {
            for (u64_t i = 0; i < PRESET_ARCH_BIT; ++i) po_del(par->node[i]);
            for (u64_t i = 0; i < par->num       ; ++i) po_del(par->sub [i]);
}

po_obj*
    po_set_root_acq
        (po_set_root* par)                                 {
            if (!par)                              return 0;
            if (po_trait_of(par) != po_set_root_t) return 0;
            if (!par->free)                                   {
                for (u64_t i = 0 ; i < par->num ; ++i)        {
                    po_obj *acq = po_set_root_acq(par->sub[i]);
                    if  (acq) return acq;
                }

                return 0;
            }

            u64_t acq_idx = po_bsr(par->free) ; if (acq_idx >= 64) return 0;
            par->free    ^= shl(1, acq_idx);
            par->use     |= shl(1, acq_idx);

            po_obj *acq = par->node[acq_idx]; par->node[acq_idx] = 0;
            po_del (acq);
            return  acq;
}

bool_t
    po_set_root_rel
        (po_set_root* par, po_obj* par_rel)                {
            if (!par)                              return 0;
            if (po_trait_of(par) != po_set_root_t) return 0;
            if (!par->use)                                    {
                if (par->num >= PRESET_ARCH_BIT)              {
                    for (u64_t i = 0; i < PRESET_ARCH_BIT; ++i)
                        if (po_set_root_rel(par->sub[i], par_rel))
                            return true_t;
                }

                po_set_root* root = po_make(po_set_root) from(0);
                if (!root)                              return false_t;
                if (po_trait_of(root) != po_set_root_t) return false_t;
                par->sub[par->num] = root;
                par->num++;
                return po_set_root_rel(root, par_rel);
            }

            u64_t rel_idx = po_bsr(par->use); if (rel_idx >= PRESET_ARCH_BIT) return 0;
            par->use     ^= shl (1, rel_idx);
            par->free    |= shl (1, rel_idx);

            par->node[rel_idx] = po_ref(par_rel);
            return true_t;
}

po_obj_trait po_set_trait = po_make_trait (
    po_set_new    ,
    po_set_clone  ,
    null_t        ,
    po_set_del    ,
    sizeof(po_set),
    null_t
);

po_obj_trait *po_set_t = &po_set_trait;

bool_t
    po_set_new
        (po_set* par_set, u32_t par_count, va_list par)  {
            par_set->set = po_make (po_set_root) from (0);

            if (!par_set->set) return false_t;
            return true_t;
}

bool_t
    po_set_clone
        (po_set* par, po_set* par_clone) {
            return false_t;
}

void
    po_set_del
        (po_set* par)       {
            po_del(par->set);
}

po_obj*
    po_set_acq
        (po_set* par)                                 {
            if (!par)                         return 0;
            if (po_trait_of(par) != po_set_t) return 0;
            return po_set_root_acq(par->set);
}

void
    po_set_rel
        (po_set* par, po_obj* par_rel)                 {
            if (!par_rel)                        return;
            if (!par)                            return;
            if (po_trait_of(par) != po_set_t)    return;

            if (po_set_root_rel(par->set, par_rel)) return; po_set_root* root = po_make (po_set_root) from (0);
            if (!root)                              return;
            root->num    = 1       ;
            root->sub[0] = par->set;
            par ->set    = root    ;
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(po_set_acq);
EXPORT_SYMBOL(po_set_rel);
EXPORT_SYMBOL(po_set_t);
#endif