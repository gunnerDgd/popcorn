#ifndef CORE_OPS_ARITH_H
#define CORE_OPS_ARITH_H

#include "../type.h"

struct pp_obj;

typedef struct pp_arith                            {
    struct pp_obj* (*add)   (struct pp_obj*, any_t);
    struct pp_obj* (*sub)   (struct pp_obj*, any_t);
    struct pp_obj* (*mul)   (struct pp_obj*, any_t);
    struct pp_obj* (*div)   (struct pp_obj*, any_t);
    struct pp_obj* (*mod)   (struct pp_obj*, any_t);
    
    void           (*add_eq)(struct pp_obj*, any_t);
    void           (*sub_eq)(struct pp_obj*, any_t);
    void           (*mul_eq)(struct pp_obj*, any_t);
    void           (*div_eq)(struct pp_obj*, any_t);
    void           (*mod_eq)(struct pp_obj*, any_t);
}   pp_arith;

#ifndef __cplusplus

#define pp_make_arith(par_add, par_sub, par_mul, par_div, par_mod, par_add_eq, par_sub_eq, par_mul_eq, par_div_eq, par_mod_eq) {\
    .add    = ((struct pp_obj*(*)(struct pp_obj*, any_t))(par_add)),   \
    .sub    = ((struct pp_obj*(*)(struct pp_obj*, any_t))(par_sub)),   \
    .mul    = ((struct pp_obj*(*)(struct pp_obj*, any_t))(par_mul)),   \
    .div    = ((struct pp_obj*(*)(struct pp_obj*, any_t))(par_div)),   \
    .mod    = ((struct pp_obj*(*)(struct pp_obj*, any_t))(par_mod)),   \
                                                                 \
    .add_eq = ((struct pp_obj*(*)(struct pp_obj*, any_t))(par_add_eq)),\
    .sub_eq = ((struct pp_obj*(*)(struct pp_obj*, any_t))(par_sub_eq)),\
    .mul_eq = ((struct pp_obj*(*)(struct pp_obj*, any_t))(par_mul_eq)),\
    .div_eq = ((struct pp_obj*(*)(struct pp_obj*, any_t))(par_div_eq)),\
    .mod_eq = ((struct pp_obj*(*)(struct pp_obj*, any_t))(par_mod_eq)),\
}

#endif

struct pp_obj* pp_add   (struct pp_obj*, any_t);
struct pp_obj* pp_sub   (struct pp_obj*, any_t);
struct pp_obj* pp_mul   (struct pp_obj*, any_t);
struct pp_obj* pp_div   (struct pp_obj*, any_t);
struct pp_obj* pp_mod   (struct pp_obj*, any_t);

struct pp_obj* pp_add_eq(struct pp_obj*, any_t);
struct pp_obj* pp_sub_eq(struct pp_obj*, any_t);
struct pp_obj* pp_mul_eq(struct pp_obj*, any_t);
struct pp_obj* pp_div_eq(struct pp_obj*, any_t);
struct pp_obj* pp_mod_eq(struct pp_obj*, any_t);

#endif