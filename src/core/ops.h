#ifndef CORE_OPS_H
#define CORE_OPS_H

#include "ops/arith.h"
#include "ops/bit.h"
#include "ops/cmp.h"
#include "ops/cast.h"

typedef struct pp_obj_ops  {
    pp_arith   *arith;
    pp_bit     *bit ;
    pp_cmp     *cmp ;
    pp_cast    *cast;
}   pp_obj_ops;

#endif