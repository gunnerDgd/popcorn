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
        (po_node* self, u32_t count, va_list arg)                          {
            po_obj* node = null_t; if (count > 0) node = va_arg(arg, any_t);
            self->node = po_ref(node);
            self->next = null_t      ;
            self->prev = null_t      ;
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
        (po_node* self, po_node* next)                           {
            if (po_trait_of(self) != po_node_t) return     null_t;
            if (!next)                          return self->next;

            if (po_trait_of(next) != po_node_t) return null_t;
            self->next = next;
            next->prev = self;
            return next;
}

po_node*
    po_node_prev
        (po_node* self, po_node* prev)                           {
            if (po_trait_of(self) != po_node_t) return     null_t;
            if (!prev)                          return self->prev;

            if (po_trait_of(prev) != po_node_t) return null_t;
            self->prev = prev;
            prev->next = self;
            return prev;
}

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(po_node_next);
EXPORT_SYMBOL(po_node_prev);
EXPORT_SYMBOL(po_node_value);
EXPORT_SYMBOL(po_node_t);
#endif