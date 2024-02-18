#ifndef __PO_DEV_CHR_WRITE_H__
#define __PO_DEV_CHR_WRITE_H__

#include <obj.h>
#include <fut.h>

extern po_obj_trait *po_chr_write_t;
typedef struct       po_chr_write { u8_t write[128]; } po_chr_write;

u64_t   po_chr_write_len  (po_chr_write*)              ;
void    po_chr_write_dest (po_chr_write*, u8_t*, u64_t);
po_fut* po_chr_write_fut  (po_chr_write*)              ;

#endif
