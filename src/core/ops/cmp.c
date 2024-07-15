#include "cmp.h"
#include "../obj.h"

pp_ord_t
    pp_ord_arg
        (struct pp_obj* self, any_t arg)             {
            if (!pp_trait_of(self)) return pp_ord_err;

            pp_obj_ops *ops = self->trait->ops; if (!ops) return pp_ord_err;
            pp_cmp     *cmp = ops ->cmp;        if (!cmp) return pp_ord_err;

            if (!cmp->ord_arg) return pp_ord_err;
            return cmp->ord_arg(self, arg);
}

pp_ord_t
    pp_ord
        (struct pp_obj* self, struct pp_obj* arg)    {
            if (!pp_trait_of(self)) return pp_ord_err;
            if (!pp_trait_of(arg))  return pp_ord_err;

            pp_obj_ops *ops = self->trait->ops; if (!ops) return pp_ord_err;
            pp_cmp     *cmp = ops ->cmp;        if (!cmp) return pp_ord_err;

            if (!cmp->ord) return pp_ord_err;
            return cmp->ord(self, arg);
}

bool_t   pp_gt_eq(struct pp_obj* self, struct pp_obj* arg) { return pp_ord(self, arg) == pp_ord_gt | pp_ord(self, arg) == pp_ord_eq; }
bool_t   pp_lt_eq(struct pp_obj* self, struct pp_obj* arg) { return pp_ord(self, arg) == pp_ord_lt | pp_ord(self, arg) == pp_ord_eq; }
bool_t   pp_gt   (struct pp_obj* self, struct pp_obj* arg) { return pp_ord(self, arg) == pp_ord_gt; }
bool_t   pp_lt   (struct pp_obj* self, struct pp_obj* arg) { return pp_ord(self, arg) == pp_ord_lt; }
bool_t   pp_eq   (struct pp_obj* self, struct pp_obj* arg) { return pp_ord(self, arg) == pp_ord_eq; }
bool_t   pp_ne   (struct pp_obj* self, struct pp_obj* arg) { return pp_ord(self, arg) != pp_ord_eq; }

bool_t   pp_gt_eq_arg(struct pp_obj* self, any_t arg) { return pp_ord_arg(self, arg) == pp_ord_gt | pp_ord_arg(self, arg) == pp_ord_eq; }
bool_t   pp_lt_eq_arg(struct pp_obj* self, any_t arg) { return pp_ord_arg(self, arg) == pp_ord_lt | pp_ord_arg(self, arg) == pp_ord_eq; }
bool_t   pp_gt_arg   (struct pp_obj* self, any_t arg) { return pp_ord_arg(self, arg) == pp_ord_gt; }
bool_t   pp_lt_arg   (struct pp_obj* self, any_t arg) { return pp_ord_arg(self, arg) == pp_ord_lt; }
bool_t   pp_eq_arg   (struct pp_obj* self, any_t arg) { return pp_ord_arg(self, arg) == pp_ord_eq; }
bool_t   pp_ne_arg   (struct pp_obj* self, any_t arg) { return pp_ord_arg(self, arg) != pp_ord_eq; }

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(pp_ord_arg);
EXPORT_SYMBOL(pp_ord);

EXPORT_SYMBOL(pp_gt_eq_arg);
EXPORT_SYMBOL(pp_lt_eq_arg);
EXPORT_SYMBOL(pp_gt_arg);
EXPORT_SYMBOL(pp_lt_arg);
EXPORT_SYMBOL(pp_eq_arg);
EXPORT_SYMBOL(pp_ne_arg);

EXPORT_SYMBOL(pp_gt_eq);
EXPORT_SYMBOL(pp_lt_eq);
EXPORT_SYMBOL(pp_gt);
EXPORT_SYMBOL(pp_lt);
EXPORT_SYMBOL(pp_eq);
EXPORT_SYMBOL(pp_ne);
#endif