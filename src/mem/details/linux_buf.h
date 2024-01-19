#ifndef __PO_MEM_LINUX_BUF_H__
#define __PO_MEM_LINUX_BUF_H__

#include "../../core.h"

extern po_obj_trait *po_buf_t;
typedef struct       po_buf  {
    po_obj  head;
    u8_t   *buf ;
    u64_t   size;
    u64_t   off ;
}   po_buf;

bool_t po_buf_new     (po_buf*, u32_t, va_list);
bool_t po_buf_clone   (po_buf*, po_buf*)       ;
void   po_buf_del     (po_buf*)                ;

u64_t po_buf_copy_from(po_buf*, void*, u64_t, u64_t);
u64_t po_buf_copy_to  (po_buf*, void*, u64_t, u64_t);
u64_t po_buf_size     (po_buf*);
u64_t po_buf_off      (po_buf*);

#endif
