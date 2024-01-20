#ifndef __PO_DEV_CHR_DEV_H__
#define __PO_DEV_CHR_DEV_H__

#include "../core.h"
#include "../mem.h"

extern  po_obj_trait *po_chr_dev_t;
typedef po_obj       *po_chr_dev  ;

i64_t po_chr_dev_read   (po_chr_dev, po_ubuf)     ;
i64_t po_chr_dev_write  (po_chr_dev, po_ubuf)     ;
i64_t po_chr_dev_control(po_chr_dev, u32_t, void*);

#endif
