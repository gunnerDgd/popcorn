#include "cmp.h"
#include "../obj.h"

po_ord_t
    po_op_ord_arg
        (struct po_obj* self, any_t arg)             {
            if (!po_trait_of(self)) return po_ord_err;

            po_obj_ops *ops = self->trait->ops; if (!ops) return po_ord_err;
            po_ops_cmp *cmp = ops ->cmp;        if (!cmp) return po_ord_err;

            if (!cmp->ord) return po_ord_err;
            return cmp->ord_arg(self, arg);
}

po_ord_t
    po_op_ord
        (struct po_obj* self, struct po_obj* arg)    {
            if (!po_trait_of(self)) return po_ord_err;
            if (!po_trait_of(arg))  return po_ord_err;

            po_obj_ops *ops = self->trait->ops; if (!ops) return po_ord_err;
            po_ops_cmp *cmp = ops ->cmp;        if (!cmp) return po_ord_err;

            if (!cmp->ord) return po_ord_err;
            return cmp->ord_arg(self, arg);
}

bool_t   po_op_gt_eq(struct po_obj* self, struct po_obj* arg) { return po_op_ord(self, arg) == po_ord_gt | po_op_ord(self, arg) == po_ord_eq; }
bool_t   po_op_lt_eq(struct po_obj* self, struct po_obj* arg) { return po_op_ord(self, arg) == po_ord_lt | po_op_ord(self, arg) == po_ord_eq; }
bool_t   po_op_gt   (struct po_obj* self, struct po_obj* arg) { return po_op_ord(self, arg) == po_ord_gt; }
bool_t   po_op_lt   (struct po_obj* self, struct po_obj* arg) { return po_op_ord(self, arg) == po_ord_lt; }
bool_t   po_op_eq   (struct po_obj* self, struct po_obj* arg) { return po_op_ord(self, arg) == po_ord_eq; }
bool_t   po_op_ne   (struct po_obj* self, struct po_obj* arg) { return po_op_ord(self, arg) != po_ord_eq; }

bool_t   po_op_gt_eq_arg(struct po_obj* self, any_t arg) { return po_op_ord_arg(self, arg) == po_ord_gt | po_op_ord_arg(self, arg) == po_ord_eq; }
bool_t   po_op_lt_eq_arg(struct po_obj* self, any_t arg) { return po_op_ord_arg(self, arg) == po_ord_lt | po_op_ord_arg(self, arg) == po_ord_eq; }
bool_t   po_op_gt_arg   (struct po_obj* self, any_t arg) { return po_op_ord_arg(self, arg) == po_ord_gt; }
bool_t   po_op_lt_arg   (struct po_obj* self, any_t arg) { return po_op_ord_arg(self, arg) == po_ord_lt; }
bool_t   po_op_eq_arg   (struct po_obj* self, any_t arg) { return po_op_ord_arg(self, arg) == po_ord_eq; }
bool_t   po_op_ne_arg   (struct po_obj* self, any_t arg) { return po_op_ord_arg(self, arg) != po_ord_eq; }

#ifdef PRESET_LINUX
#include <linux/module.h>
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(po_op_ord_arg);
EXPORT_SYMBOL(po_op_ord);

EXPORT_SYMBOL(po_op_gt_eq_arg);
EXPORT_SYMBOL(po_op_lt_eq_arg);
EXPORT_SYMBOL(po_op_gt_arg);
EXPORT_SYMBOL(po_op_lt_arg);
EXPORT_SYMBOL(po_op_eq_arg);
EXPORT_SYMBOL(po_op_ne_arg);

EXPORT_SYMBOL(po_op_gt_eq);
EXPORT_SYMBOL(po_op_lt_eq);
EXPORT_SYMBOL(po_op_gt);
EXPORT_SYMBOL(po_op_lt);
EXPORT_SYMBOL(po_op_eq);
EXPORT_SYMBOL(po_op_ne);
#endif