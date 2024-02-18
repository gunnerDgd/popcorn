#ifndef __OPS_CMP_H__
#define __OPS_CMP_H__

#include "../type.h"

struct po_obj;

typedef enum po_ord_t {
    po_ord_err = -1,
    po_ord_lt  =  0,
    po_ord_eq  =  1,
    po_ord_gt  =  2
}   po_ord_t;

typedef struct po_ops_cmp                 {
    po_ord_t (*ord)(struct po_obj*, any_t);
}   po_ops_cmp;

#define po_make_cmp_ops(par_ord) { .ord = ((po_ord_t (*)(struct po_obj*, any_t))(par_ord)) }

po_ord_t po_op_ord  (struct po_obj*, any_t);
bool_t   po_op_gt   (struct po_obj*, any_t);
bool_t   po_op_gt_eq(struct po_obj*, any_t);
bool_t   po_op_lt   (struct po_obj*, any_t);
bool_t   po_op_lt_eq(struct po_obj*, any_t);
bool_t   po_op_eq   (struct po_obj*, any_t);
bool_t   po_op_ne   (struct po_obj*, any_t);

#endif