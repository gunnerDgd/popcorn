#include "cmp.h"
#include "../obj.h"

pp_ord_t
    pp_ord
        (struct pp_obj* self, any_t arg)             {
            if (!pp_trait_of(self)) return pp_ord_err;
            pp_obj_ops *ops = null_t;
            pp_cmp     *cmp = null_t;

            ops = self->trait->ops; if (!ops) return pp_ord_err;
            cmp = ops ->cmp;        if (!cmp) return pp_ord_err;

            if (!cmp->ord) return pp_ord_err;
            return cmp->ord(self, arg);
}

bool_t pp_gt_eq(struct pp_obj* self, any_t arg) { return pp_ord(self, arg) == pp_ord_gt | pp_ord(self, arg) == pp_ord_eq; }
bool_t pp_lt_eq(struct pp_obj* self, any_t arg) { return pp_ord(self, arg) == pp_ord_lt | pp_ord(self, arg) == pp_ord_eq; }
bool_t pp_gt   (struct pp_obj* self, any_t arg) { return pp_ord(self, arg) == pp_ord_gt; }
bool_t pp_lt   (struct pp_obj* self, any_t arg) { return pp_ord(self, arg) == pp_ord_lt; }
bool_t pp_eq   (struct pp_obj* self, any_t arg) { return pp_ord(self, arg) == pp_ord_eq; }
bool_t pp_ne   (struct pp_obj* self, any_t arg) { return pp_ord(self, arg) != pp_ord_eq; }

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(pp_ord);
EXPORT_SYMBOL(pp_gt_eq);
EXPORT_SYMBOL(pp_lt_eq);
EXPORT_SYMBOL(pp_gt);
EXPORT_SYMBOL(pp_lt);
EXPORT_SYMBOL(pp_eq);
EXPORT_SYMBOL(pp_ne);
#endif