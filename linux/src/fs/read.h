#ifndef __PO_FS_READ_H__
#define __PO_FS_READ_H__

#include "obj.h"
#include "fut.h"

#include <linux/uaccess.h>

struct po_file;
extern po_obj_trait *po_read_t;
typedef struct       po_read  {
    po_obj          head;
    struct po_file *file;
    __user u8_t    *read;
    u64_t           stat;
    u64_t           len;
    u64_t           ret;
}   po_read;

bool_t  po_read_new  (po_read*, u32_t, va_list);
bool_t  po_read_clone(po_read*, po_read*)      ;
void    po_read_del  (po_read*)                ;

void    po_read_src  (po_read*, u8_t*, u64_t);
u64_t   po_read_len  (po_read*)              ;
po_fut* po_read_fut  (po_read*)              ;

#endif