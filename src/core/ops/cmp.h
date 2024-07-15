#ifndef CORE_OPS_CMP_H
#define CORE_OPS_CMP_H

#include "../type.h"

struct pp_obj;

typedef enum pp_ord_t {
    pp_ord_err = -1,
    pp_ord_lt  =  0,
    pp_ord_eq  =  1,
    pp_ord_gt  =  2
}   pp_ord_t;

typedef struct pp_cmp                        {
    pp_ord_t (*ord_arg)(struct pp_obj*, any_t);
    pp_ord_t (*ord)    (struct pp_obj*, any_t);
}   pp_cmp;

#define pp_make_cmp(do_ord_arg, do_ord)                           {\
    .ord_arg = ((pp_ord_t (*)(struct pp_obj*, any_t))(do_ord_arg)),\
    .ord     = ((pp_ord_t (*)(struct pp_obj*, any_t))(do_ord))     \
}

pp_ord_t pp_ord_arg  (struct pp_obj*, any_t);
pp_ord_t pp_ord      (struct pp_obj*, struct pp_obj*);

bool_t   pp_gt       (struct pp_obj*, struct pp_obj*);
bool_t   pp_gt_eq    (struct pp_obj*, struct pp_obj*);
bool_t   pp_lt       (struct pp_obj*, struct pp_obj*);
bool_t   pp_lt_eq    (struct pp_obj*, struct pp_obj*);
bool_t   pp_eq       (struct pp_obj*, struct pp_obj*);
bool_t   pp_ne       (struct pp_obj*, struct pp_obj*);

bool_t   pp_gt_eq_arg(struct pp_obj*, any_t);
bool_t   pp_gt_arg   (struct pp_obj*, any_t);
bool_t   pp_lt_eq_arg(struct pp_obj*, any_t);
bool_t   pp_lt_arg   (struct pp_obj*, any_t);
bool_t   pp_eq_arg   (struct pp_obj*, any_t);
bool_t   pp_ne_arg   (struct pp_obj*, any_t);

#endif