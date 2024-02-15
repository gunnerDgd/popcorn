#ifndef __OPS_H__
#define __OPS_H__

#include "ops/arith.h"
#include "ops/bit.h"
#include "ops/cmp.h"
#include "ops/logical.h"
#include "ops/cast.h"

typedef struct po_obj_ops  {
    po_ops_arith   *arith  ;
    po_ops_bit     *bit    ;
    po_ops_cmp     *cmp    ;
    po_ops_logical *logical;
    po_ops_cast    *cast   ;
}   po_obj_ops;

#endif