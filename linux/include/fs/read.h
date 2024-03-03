#ifndef __PO_FS_READ_H__
#define __PO_FS_READ_H__

#include <obj.h>
#include <fut.h>

extern po_obj_trait *po_read_t;
typedef struct       po_read  { u8_t po_read[128]; } po_read;

void    po_read_src  (po_read*, u8_t*, u64_t);
u64_t   po_read_len  (po_read*)              ;
po_fut* po_read_fut  (po_read*)              ;

#endif