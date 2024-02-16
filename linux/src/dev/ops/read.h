#ifndef __PO_DEV_OPS_READ_H__
#define __PO_DEV_OPS_READ_H__

#include <obj.h>
#include <fut.h>

#include <linux/uaccess.h>

extern po_obj_trait *po_read_t;
typedef struct       po_read  {
    po_obj       head;
    u64_t        stat;
    __user u8_t *dest;
    u8_t        *src;
    u64_t        len;
    u64_t        ret;
}   po_read;

bool_t  po_read_new  (po_read*, u32_t, va_list);
bool_t  po_read_clone(po_read*, po_read*)      ;
void    po_read_del  (po_read*)                ;

u64_t   po_read_len  (po_read*)              ;
void    po_read_src  (po_read*, u8_t*, u64_t);
po_fut* po_read_fut  (po_read*)              ;

#endif