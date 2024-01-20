#ifndef __PO_MEM_UBUF_H__
#define __PO_MEM_UBUF_H__

#include "../core.h"

extern  po_obj_trait *po_ubuf_t;
typedef po_obj       *po_ubuf  ;

u64_t po_ubuf_copy_from(po_ubuf, void*, u64_t, u64_t);
u64_t po_ubuf_copy_to  (po_ubuf, void*, u64_t, u64_t);
u64_t po_ubuf_size     (po_ubuf);
u64_t po_ubuf_off      (po_ubuf);

#endif