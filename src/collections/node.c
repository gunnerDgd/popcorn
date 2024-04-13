#include "node.h"

po_obj_trait po_node_trait = po_make_trait (
    po_node_new    ,
    po_node_clone  ,
    null_t         ,
    po_node_del    ,
    sizeof(po_node),
    null_t
);

po_obj_trait* po_node_t = &po_node_trait;

bool_t
    po_node_new
        (po_node* par_cur, u32_t par_count, va_list par)                                {
            po_obj* node  = null_t      ; if (par_count > 0) node = va_arg(par, po_obj*);
            par_cur->node = po_ref(node);
            par_cur->next = null_t      ;
            par_cur->prev = null_t      ;
            return true_t;
}

bool_t
    po_node_clone
        (po_node* par, po_node* par_clone) {
            return false_t;
}

void
    po_node_del
        (po_node* par)                                   {
            if    (par->prev) par->prev->next = par->next;
            if    (par->next) par->next->prev = par->prev;
            po_del(par->node);
}

po_obj*
    po_node_value
        (po_node* par)                                      {
            if (!par)                          return null_t;
            if (po_trait_of(par) != po_node_t) return null_t;
            return par->node;
}

po_node*
    po_node_next
        (po_node* par, po_node* par_next)                      {
            if (!par)                             return null_t;
            if (po_trait_of(par) != po_node_t)    return null_t;
            if (par_next)                                            {
                if (po_trait_of(par_next) != po_node_t) return null_t;
                par     ->next = par_next;
                par_next->prev = par     ;
                return par_next;
            }

            return par->next;
}

po_node*
    po_node_prev
        (po_node* par, po_node* par_prev)                            {
            if (!par)                                   return null_t;
            if (po_trait_of(par) != po_node_t)          return null_t;
            if (par_prev)                                            {
                if (po_trait_of(par_prev) != po_node_t) return null_t;
                par     ->prev = par_prev;
                par_prev->next = par     ;
                return par_prev;
            }

            return par->prev;
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(po_node_next);
EXPORT_SYMBOL(po_node_prev);
EXPORT_SYMBOL(po_node_value);
EXPORT_SYMBOL(po_node_t);
#endif