#ifndef __PO_H__
#define __PO_H__

#include "core/atom.h"
#include "core/bit.h"
#include "core/box.h"
#include "core/endian.h"
#include "core/fut.h"
#include "core/mem.h"
#include "core/obj.h"
#include "core/ops.h"
#include "core/print.h"
#include "core/macro.h"
#include "core/task.h"
#include "core/type.h"
#include "core/this.h"

extern po_mem_ops *po_heap_ops_atomic;
extern po_mem_ops *po_heap_ops;

extern po_mem     *po_heap_atomic;
extern po_mem     *po_heap;

extern po_obj_trait *po_t;
struct               po  {
    po_obj head;
};

extern struct po po;

#endif