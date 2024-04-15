#ifndef __PO_FS_CHR_CHR_TYPE_H__
#define __PO_FS_CHR_CHR_TYPE_H__

#include <core.h>
#include <collections.h>
#include <linux/cdev.h>
#include <linux/fs.h>

struct po_file_type;
extern po_obj_trait *po_chr_type_t;
typedef struct       po_chr_type  {
    po_obj     head;
    struct ida ida;
    dev_t      maj;
    u64_t      num;
}   po_chr_type;

bool_t po_chr_type_new  (po_chr_type*, u32_t, va_list);
bool_t po_chr_type_clone(po_chr_type*, po_chr_type*)  ;
void   po_chr_type_del  (po_chr_type*)                ;

#endif