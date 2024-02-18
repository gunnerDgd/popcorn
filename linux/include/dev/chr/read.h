#ifndef __PO_DEV_CHR_READ_H__
#define __PO_DEV_CHR_READ_H__

#include <obj.h>
#include <fut.h>

extern po_obj_trait *po_chr_read_t;
typedef struct       po_chr_read { u8_t read[128]; } po_chr_read;

u64_t   po_chr_read_len  (po_chr_read*)              ;
void    po_chr_read_src  (po_chr_read*, u8_t*, u64_t);
po_fut* po_chr_read_fut  (po_chr_read*)              ;

#endif
