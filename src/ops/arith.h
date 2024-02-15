#ifndef __OPS_ARITH_H__
#define __OPS_ARITH_H__

#include "../type.h"

struct po_obj;

typedef struct po_ops_arith                        {
    struct po_obj* (*add)   (struct po_obj*, any_t);
    struct po_obj* (*sub)   (struct po_obj*, any_t);
    struct po_obj* (*mul)   (struct po_obj*, any_t);
    struct po_obj* (*div)   (struct po_obj*, any_t);
    struct po_obj* (*mod)   (struct po_obj*, any_t);
    
    void           (*add_eq)(struct po_obj*, any_t);
    void           (*sub_eq)(struct po_obj*, any_t);
    void           (*mul_eq)(struct po_obj*, any_t);
    void           (*div_eq)(struct po_obj*, any_t);
    void           (*mod_eq)(struct po_obj*, any_t);
}   po_ops_arith;

#ifndef __cplusplus

#define po_make_arith_ops(par_add, par_sub, par_mul, par_div, par_mod, par_add_eq, par_sub_eq, par_mul_eq, par_div_eq, par_mod_eq) {\
    .add    = ((struct po_obj*(*)(struct po_obj*, any_t))(par_add)),   \
    .sub    = ((struct po_obj*(*)(struct po_obj*, any_t))(par_sub)),   \
    .mul    = ((struct po_obj*(*)(struct po_obj*, any_t))(par_mul)),   \
    .div    = ((struct po_obj*(*)(struct po_obj*, any_t))(par_div)),   \
    .mod    = ((struct po_obj*(*)(struct po_obj*, any_t))(par_mod)),   \
                                                                 \
    .add_eq = ((struct po_obj*(*)(struct po_obj*, any_t))(par_add_eq)),\
    .sub_eq = ((struct po_obj*(*)(struct po_obj*, any_t))(par_sub_eq)),\
    .mul_eq = ((struct po_obj*(*)(struct po_obj*, any_t))(par_mul_eq)),\
    .div_eq = ((struct po_obj*(*)(struct po_obj*, any_t))(par_div_eq)),\
    .mod_eq = ((struct po_obj*(*)(struct po_obj*, any_t))(par_mod_eq)),\
}

#endif

struct po_obj* po_op_add   (struct po_obj*, any_t);
struct po_obj* po_op_sub   (struct po_obj*, any_t);
struct po_obj* po_op_mul   (struct po_obj*, any_t);
struct po_obj* po_op_div   (struct po_obj*, any_t);
struct po_obj* po_op_mod   (struct po_obj*, any_t);

struct po_obj* po_op_add_eq(struct po_obj*, any_t);
struct po_obj* po_op_sub_eq(struct po_obj*, any_t);
struct po_obj* po_op_mul_eq(struct po_obj*, any_t);
struct po_obj* po_op_div_eq(struct po_obj*, any_t);
struct po_obj* po_op_mod_eq(struct po_obj*, any_t);

#endif