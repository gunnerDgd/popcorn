#ifndef CORE_OPS_BIT_H
#define CORE_OPS_BIT_H

#include "../type.h"

struct pp_obj;

typedef struct pp_bit                              {
    struct pp_obj* (*and)   (struct pp_obj*, any_t);
    struct pp_obj* (*or)    (struct pp_obj*, any_t);
    struct pp_obj* (*xor)   (struct pp_obj*, any_t);
    struct pp_obj* (*not)   (struct pp_obj*)       ;

    void        (*and_eq)(struct pp_obj*, any_t);
    void        (*or_eq) (struct pp_obj*, any_t);
    void        (*xor_eq)(struct pp_obj*, any_t);
}   pp_bit;

#ifndef __cplusplus
#define pp_make_bit (par_and, par_or, par_xor, par_and_eq, par_or_eq, par_xor_eq) {\
    .and    = ((struct pp_obj*(*)(struct pp_obj*, any_t))(par_and)),   \
    .or     = ((struct pp_obj*(*)(struct pp_obj*, any_t))(par_or)) ,   \
    .xor    = ((struct pp_obj*(*)(struct pp_obj*, any_t))(par_xor)),   \
    .not    = ((struct pp_obj*(*)(struct pp_obj*))       (par_not)),   \
                                                                       \
    .and_eq = ((struct pp_obj*(*)(struct pp_obj*, any_t))(par_and_eq)),\
    .or_eq  = ((struct pp_obj*(*)(struct pp_obj*, any_t))(par_or_eq)) ,\
    .xor_eq = ((struct pp_obj*(*)(struct pp_obj*, any_t))(par_xor_eq)) \
}
#endif

struct pp_obj* pp_bit_and   (struct pp_obj*, any_t);
struct pp_obj* pp_bit_or    (struct pp_obj*, any_t);
struct pp_obj* pp_bit_xor   (struct pp_obj*, any_t);
struct pp_obj* pp_bit_not   (struct pp_obj*)       ;

struct pp_obj* pp_bit_and_eq(struct pp_obj*, any_t);
struct pp_obj* pp_bit_or_eq (struct pp_obj*, any_t);
struct pp_obj* pp_bit_xor_eq(struct pp_obj*, any_t);

#endif