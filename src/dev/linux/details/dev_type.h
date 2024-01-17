#ifndef __PO_LINUX_DEV_TYPE_H__
#define __PO_LINUX_DEV_TYPE_H__

#include "../../../core.h"

#include <linux/cdev.h>
#include <linux/fs.h>

struct po_dev     ;
struct po_dev_type;

extern po_obj_trait *po_dev_type_t;
typedef struct       po_dev_type  {
    po_obj         head     ;
    po_str         name     ;
    struct class  *cls      ;
    struct cdev    hnd      ;
    dev_t          id       ;

    u64_t          dev_num  ;
    struct po_dev* dev[1 MB];
    po_list        active   ;
    po_list        free     ;
}   po_dev_type;

extern po_dev_type*           dev_type[4096];
extern struct file_operations dev_type_ops  ;

bool_t  po_dev_type_new  (po_dev_type*, u32_t, va_list);
bool_t  po_dev_type_clone(po_dev_type*, po_dev_type*)  ;
void    po_dev_type_del  (po_dev_type*)                ;

MODULE_LICENSE("GPL");

#endif