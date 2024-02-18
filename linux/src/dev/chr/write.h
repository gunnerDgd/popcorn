#ifndef __PO_DEV_CHR_WRITE_H__
#define __PO_DEV_CHR_WRITE_H__

#include "obj.h"
#include "fut.h"

#include <linux/uaccess.h>

struct po_chr_dev;

extern po_obj_trait *po_chr_write_t;
typedef struct       po_chr_write  {
    po_obj             head ;
    u64_t              stat ;
    __user u8_t       *write;
    struct po_chr_dev *dev;
    u64_t              len;
    u64_t              ret;
}   po_chr_write;

bool_t  po_chr_write_new  (po_chr_write*, u32_t, va_list);
bool_t  po_chr_write_clone(po_chr_write*, po_chr_write*) ;
void    po_chr_write_del  (po_chr_write*)                ;

u64_t   po_chr_write_len  (po_chr_write*)              ;
void    po_chr_write_dest (po_chr_write*, u8_t*, u64_t);
po_fut* po_chr_write_fut  (po_chr_write*)              ;

#endif