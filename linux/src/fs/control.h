#ifndef __PO_DEV_CHR_CON_H__
#define __PO_DEV_CHR_CON_H__

#include <core.h>
#include <collections.h>

struct po_chr_dev;

extern po_obj_trait *po_control_t;
typedef struct       po_control  {
    po_obj          head;
    struct po_file *file;
    u64_t stat;
    u64_t code;
    any_t arg;
    u64_t ret;
}   po_control;

bool_t  po_control_new  (po_control*, u32_t, va_list);
bool_t  po_control_clone(po_control*, po_control*)   ;
void    po_control_del  (po_control*);

void    po_control_ready(po_control*, u64_t);
u64_t   po_control_code (po_control*)       ;
any_t   po_control_arg  (po_control*)       ;
po_fut* po_control_fut  (po_control*)       ;

#endif