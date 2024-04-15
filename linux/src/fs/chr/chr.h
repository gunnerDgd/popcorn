#ifndef __PO_FS_CHR_CHR_H__
#define __PO_FS_CHR_CHR_H__

#include <core.h>
#include <collections.h>
#include <linux/cdev.h>

struct po_class;
struct po_file_type;
struct po_chr_type;

extern po_obj_trait *po_chr_t;
typedef struct       po_chr   {
    po_obj               head ;
    struct po_class     *class;
    struct po_file_type *file;
    struct po_chr_type  *type;
    struct device       *dev;
    struct cdev          chr;
    dev_t                num;
}   po_chr;

bool_t po_chr_new  (po_chr*, u32_t, va_list);
bool_t po_chr_clone(po_chr*, po_chr*)       ;
void   po_chr_del  (po_chr*)                ;

#endif
