#ifndef __PO_DEV_CHR_READ_H__
#define __PO_DEV_CHR_READ_H__

#include "obj.h"
#include "fut.h"

#include <linux/uaccess.h>

struct po_chr_dev;

extern po_obj_trait *po_chr_read_t;
typedef struct       po_chr_read  {
    po_obj             head;
    u64_t              stat;
    __user u8_t       *read;
    struct po_chr_dev *dev;
    u64_t              len;
    u64_t              ret;
}   po_chr_read;

bool_t  po_chr_read_new  (po_chr_read*, u32_t, va_list);
bool_t  po_chr_read_clone(po_chr_read*, po_chr_read*)  ;
void    po_chr_read_del  (po_chr_read*)                ;

u64_t   po_chr_read_len  (po_chr_read*)              ;
void    po_chr_read_src  (po_chr_read*, u8_t*, u64_t);
po_fut* po_chr_read_fut  (po_chr_read*)              ;

#endif