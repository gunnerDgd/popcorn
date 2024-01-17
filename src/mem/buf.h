#ifndef __PO_MEM_BUF_H__
#define __PO_MEM_BUF_H__

#ifdef PO_PRESET_LINUX
#include "linux/details/buf.h"
#endif

u64_t po_buf_copy_from(po_buf*, void*, u64_t, u64_t);
u64_t po_buf_copy_to  (po_buf*, void*, u64_t, u64_t);
u64_t po_buf_size     (po_buf*);
u64_t po_buf_off      (po_buf*);

#endif
