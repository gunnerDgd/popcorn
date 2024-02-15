#ifndef __OPS_BIT_H__
#define __OPS_BIT_H__

#include "../type.h"

struct po_obj;

typedef struct po_ops_bit                       {
    struct po_obj* (*and)   (struct po_obj*, any_t);
    struct po_obj* (*or)    (struct po_obj*, any_t);
    struct po_obj* (*xor)   (struct po_obj*, any_t);
    struct po_obj* (*not)   (struct po_obj*)       ;
    
    void        (*and_eq)(struct po_obj*, any_t);
    void        (*or_eq) (struct po_obj*, any_t);
    void        (*xor_eq)(struct po_obj*, any_t);
}   po_ops_bit;

#ifndef __cplusplus

#define po_make_bit_ops (par_and, par_or, par_xor, par_and_eq, par_or_eq, par_xor_eq) {\
    .and    = ((struct po_obj*(*)(struct po_obj*, any_t))(par_and)),   \
    .or     = ((struct po_obj*(*)(struct po_obj*, any_t))(par_or)) ,   \
    .xor    = ((struct po_obj*(*)(struct po_obj*, any_t))(par_xor)),   \
    .not    = ((struct po_obj*(*)(struct po_obj*))       (par_not)),   \
                                                                 \
    .and_eq = ((struct po_obj*(*)(struct po_obj*, any_t))(par_and_eq)),\
    .or_eq  = ((struct po_obj*(*)(struct po_obj*, any_t))(par_or_eq)) ,\
    .xor_eq = ((struct po_obj*(*)(struct po_obj*, any_t))(par_xor_eq)) \
}

#endif

struct po_obj* po_op_and   (struct po_obj*, any_t);
struct po_obj* po_op_or    (struct po_obj*, any_t);
struct po_obj* po_op_xor   (struct po_obj*, any_t);
struct po_obj* po_op_not   (struct po_obj*)       ;

struct po_obj* po_op_and_eq(struct po_obj*, any_t);
struct po_obj* po_op_or_eq (struct po_obj*, any_t);
struct po_obj* po_op_xor_eq(struct po_obj*, any_t);

#endif