#ifndef __PO_BUF_H__
#define __PO_BUF_H__

#include "../core.h"

extern  po_obj_trait *po_buf_t;
typedef po_obj       *po_buf  ;

u64_t po_buf_copy_from(po_buf, void*, u64_t, u64_t);
u64_t po_buf_copy_to  (po_buf, void*, u64_t, u64_t);
u64_t po_buf_size     (po_buf);
u64_t po_buf_off      (po_buf);

#endif