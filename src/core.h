#ifndef __PO_CORE_H__
#define __PO_CORE_H__

#include "core/sync/spsc.h"
#include "core/sync/spmc.h"
#include "core/sync/mpsc.h"
#include "core/sync/mpmc.h"

#include "core/atom.h"
#include "core/bit.h"
#include "core/box.h"
#include "core/endian.h"
#include "core/fut.h"
#include "core/mem.h"
#include "core/obj.h"
#include "core/ops.h"
#include "core/print.h"
#include "core/type.h"

extern po_obj_trait *po_core_t;
struct               po_core  {
    po_obj  head;
    po_mem  heap;
    po_mem *mem;
};

extern struct po_core po_core;

bool_t po_core_new  (struct po_core*, u32_t, va_list) ;
bool_t po_core_clone(struct po_core*, struct po_core*);
bool_t po_core_ref  (struct po_core*);
void   po_core_del  (struct po_core*);

#endif