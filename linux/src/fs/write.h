#ifndef __PO_FS_WRITE_H__
#define __PO_FS_WRITE_H__

#include <core.h>
#include <collections.h>
#include <linux/uaccess.h>

struct po_chr_dev;

extern po_obj_trait *po_write_t;
typedef struct       po_write  {
    po_obj          head;
    struct po_file *file;
    u64_t           stat;
    __user u8_t    *buf ;
    u64_t           len ;
    u64_t           off ;
}   po_write;

bool_t      po_write_new       (po_write*, u32_t, va_list);
bool_t      po_write_clone     (po_write*, po_write*)     ;
void        po_write_del       (po_write*)                ;

void        po_write_to        (po_write*, u8_t*, u64_t)  ;
void        po_write_ready     (po_write*)                ;
void        po_write_err       (po_write*, u64_t)         ;

u8_t*       po_write_buf       (po_write*)                ;
u64_t       po_write_len       (po_write*)                ;
po_fut*     po_write_fut       (po_write*)                ;

#endif