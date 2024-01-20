#ifndef __PO_DEV_CHR_DEV_H__
#define __PO_DEV_CHR_DEV_H__

#include "../core.h"
#include "../mem.h"
#include "dev.h"
#include "chr.h"

extern po_obj_trait *po_chr_dev_t;
typedef struct       po_chr_dev  {
    po_obj  head;
    po_chr *chr ;
    void   *dev ;
}   po_chr_dev  ;

bool_t po_chr_dev_new    (po_chr_dev*, u32_t, va_list);
bool_t po_chr_dev_clone  (po_chr_dev*, po_chr_dev*)   ;
void   po_chr_dev_del    (po_chr_dev*)                ;

i64_t  po_chr_dev_read   (po_chr_dev*, po_buf*)       ;
i64_t  po_chr_dev_write  (po_chr_dev*, po_buf*)       ;
i64_t  po_chr_dev_control(po_chr_dev*, u32_t, void*)  ;

#endif