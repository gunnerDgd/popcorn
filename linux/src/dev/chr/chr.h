#ifndef __PO_DEV_CHR_CHR_H__
#define __PO_DEV_CHR_CHR_H__

#include "obj.h"
#include "str.h"
#include "set.h"

#include <linux/cdev.h>
#include <linux/fs.h>

struct po_chr_dev;
struct po_chr    ;

extern po_obj_trait *po_chr_t;
typedef struct       po_chr  {
    po_obj head;
    po_str name;
    po_set type;
    u64_t  min;
    dev_t  maj;
}   po_chr;

bool_t po_chr_new  (po_chr*, u32_t, va_list);
bool_t po_chr_clone(po_chr*, po_chr*)       ;
void   po_chr_del  (po_chr*)                ;

#endif