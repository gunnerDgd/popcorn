#ifndef __PO_MEM_LINUX_UBUF_H__
#define __PO_MEM_LINUX_UBUF_H__

#include "../../core.h"

extern po_obj_trait *po_ubuf_t;
typedef struct       po_ubuf  {
    po_obj  head;
    u8_t   *buf ;
    u64_t   size;
    u64_t   off ;
}   po_ubuf;

bool_t po_ubuf_new     (po_ubuf*, u32_t, va_list);
bool_t po_ubuf_clone   (po_ubuf*, po_ubuf*)      ;
void   po_ubuf_del     (po_ubuf*)                ;

u64_t po_ubuf_copy_from(po_ubuf*, void*, u64_t, u64_t);
u64_t po_ubuf_copy_to  (po_ubuf*, void*, u64_t, u64_t);
u64_t po_ubuf_size     (po_ubuf*);
u64_t po_ubuf_off      (po_ubuf*);

#endif
