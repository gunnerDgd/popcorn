#ifndef __PO_DEV_OPS_WRITE_H__
#define __PO_DEV_OPS_WRITE_H__

#include <obj.h>
#include <fut.h>

#include <linux/uaccess.h>

extern po_obj_trait *po_write_t;
typedef struct       po_write  {
    po_obj       head;
    u64_t        stat;
    u8_t        *dest;
    __user u8_t *src;
    u64_t        len;
    u64_t        ret;
}   po_write;

bool_t  po_write_new  (po_write*, u32_t, va_list);
bool_t  po_write_clone(po_write*, po_write*)     ;
void    po_write_del  (po_write*)                ;

u64_t   po_write_len  (po_write*)              ;
void    po_write_dest (po_write*, u8_t*, u64_t);
po_fut* po_write_fut  (po_write*)              ;

#endif