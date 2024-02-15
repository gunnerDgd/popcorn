#ifndef __OPS_LOGICAL_H__
#define __OPS_LOGICAL_H__

#include "../type.h"

struct po_obj;

typedef struct po_ops_logical                   {
    struct po_obj* (*and)(struct po_obj*, any_t);
    struct po_obj* (*or) (struct po_obj*, any_t);
    struct po_obj* (*not)(struct po_obj*)       ;
}   po_ops_logical;

#ifndef __cplusplus

#define po_make_logical_ops (par_and, par_or, par_not)    {\
    .and = ((struct obj*(*)(struct obj*, any_t))(par_and)),\
    .or  = ((struct obj*(*)(struct obj*, any_t))(par_or)) ,\
    .not = ((struct obj*(*)(struct obj*))       (par_not)) \
}

#endif

struct po_obj* po_log_and(struct po_obj*, any_t);
struct po_obj* po_log_or (struct po_obj*, any_t);
struct po_obj* po_log_not(struct po_obj*)       ;

#endif