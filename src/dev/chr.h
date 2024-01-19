#ifndef __PO_CHR_H__
#define __PO_CHR_H__

#ifdef PO_PRESET_LINUX
#include "details/linux_chr.h"
#endif

#include "ns.h"
#include "dev.h"

#include "../mem.h"

typedef void* po_chr_dev;
po_chr_dev    po_chr_dev_new    (const char*, po_ns*, po_chr*, po_dev_ops*, po_obj*);
void          po_chr_dev_del    (po_chr_dev)                                        ;

i64_t         po_chr_dev_read   (po_chr_dev, po_buf*)     ;
i64_t         po_chr_dev_write  (po_chr_dev, po_buf*)     ;
i64_t         po_chr_dev_control(po_chr_dev, u32_t, void*);

#endif